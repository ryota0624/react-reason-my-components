include FlexibleTableHeader;

type element;

[@bs.send]
external addEventListener : (Dom.element, string, unit => unit) => unit =
  "addEventListener";
module Fragment = {
  [@bs.module "react"] external fragment : ReasonReact.reactClass = "Fragment";
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=fragment,
      ~props=Js.Obj.empty(),
      children,
    );
};

type tableCell('column) = {
  column: 'column,
  style: ReactDOMRe.style,
};

module type TableDef = {
  type column;
  type relationDataType;
  type header = headerItem(column);
  type cell = tableCell(column);
  let dataRowStyle: (list(header), relationDataType) => string;
  let headerRowStyle: list(header) => string;
  let footerRowStyle: list(header) => string;

  let defaultHeader: column => header;
};

module FlexibleTable = (T: TableDef) => {
  type state = {
    tableWidth: float,
    mutable tableDom: option(Dom.element),
  };
  type action =
    | DetectedTableSize(float);
  let defaultHeaders = headerColumns =>
    headerColumns |> List.map(T.defaultHeader);
  let headerItemToCell = (header: T.header) : T.cell => {
    let width = getWidthSize(header.size);
    let px = "px";
    {
      column: header.column,
      style: ReactDOMRe.Style.make(~width={j|$width$px|j}, ()),
    };
  };
  let apperTable = (theRef, {ReasonReact.send, ReasonReact.state}) => {
    let domOpt = Js.Nullable.toOption(theRef);
    let tableDomToAction = tableDom => {
      let tableWidth: float = ReactDOMRe.domElementToObj(tableDom)##clientWidth;
      if (tableWidth != state.tableWidth) {
        DetectedTableSize(tableWidth) |> send;
      };
    };
    switch (domOpt) {
    | Some(dom) =>
      state.tableDom = Some(dom);
      let tableDom = dom;

      addEventListener(dom, "transitionend", () =>
        switch (state.tableDom) {
        | Some(dom) => tableDomToAction(dom)
        | None => ()
        }
      );

      tableDomToAction(tableDom);
    | None => ()
    };
  };

  let component = ReasonReact.reducerComponent("FlexibleTable");
  let make =
      (
        ~datas: list('data),
        ~headerItems: list(T.header),
        ~row: (list(T.cell), 'data) => ReasonReact.reactElement,
        ~header: list(T.cell) => ReasonReact.reactElement,
        ~footer: list(T.cell) => ReasonReact.reactElement,
        ~tableClassName: string,
        _chiildren,
      ) => {
    ...component,
    initialState: () => {tableWidth: 0.0, tableDom: None},
    reducer: (action, state) =>
      switch (action) {
      | DetectedTableSize(tableWidth) =>
        ReasonReact.Update({...state, tableWidth})
      },
    render: self => {
      let cells =
        headerItems
        |> getWidthSizeByTableWidthSize(self.state.tableWidth)
        |> List.map(headerItemToCell);
      let bodyRows =
        datas |> List.map(row(cells)) |> Array.of_list |> ReasonReact.array;

      let header = cells |> header;
      let footer = cells |> footer;
      <table className=tableClassName ref=(self.handle(apperTable))>
        <thead> header </thead>
        <tbody> bodyRows </tbody>
        <tfoot> footer </tfoot>
      </table>;
    },
  };
};
