open FlexibleTableHeader
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
  style: ReactDOMRe.style
};

module type TableDef = {
  type column;
  type relationDataType;
  type header = headerItem(column);
  type cell = tableCell(column);
  let dataRowStyle: list(header) => relationDataType => string;
  let headerRowStyle: list(header) => string;
  let footerRowStyle: list(header) => string;

  let defaultHeader: column => header
};

module FlexibleTable = (Def: TableDef) => {
  type state = {
    tableWidth: float
  };
  type action = DetectedTableSize(float);
  let defaultHeaders = headerColumns => headerColumns |> List.map(Def.defaultHeader)
  let headerItemToCell = (header: Def.header): Def.cell => {
    let width = getWidthSize(header.size) |> string_of_float;
      {
        column: header.column, 
        style: ReactDOMRe.Style.make(~width={|"${width}px"|}, ())
      }
    }
  let apperTable = (theRef, {ReasonReact.send}) => {
    let domOpt = Js.Nullable.toOption(theRef);
    switch (domOpt) {
      | Some(dom) => DetectedTableSize(ReactDOMRe.domElementToObj(dom)##width) |> send
      | None => ()
      };
    /* wondering about Js.Nullable.toOption? See the note below */
  };
  
  let component = ReasonReact.reducerComponent("FlexibleTable");
  let make =
      (
        ~datas: list('data),
        ~headerItems: list(Def.header),
        ~row: (list(Def.cell), 'data) => ReasonReact.reactElement,
        ~header: list(Def.cell) => ReasonReact.reactElement,
        ~footer: list(Def.cell) => ReasonReact.reactElement,
        ~tableName: string,
        _chiildren,
      ) => {
    ...component,
    initialState: () => {tableWidth: 0.0},
    reducer: (action, _) => 
      switch (action) {
        | DetectedTableSize(tableWidth) => ReasonReact.Update({tableWidth: tableWidth})
      },
    render: self => {
      let cells= headerItems |> getWidthSizeByTableWidthSize(self.state.tableWidth) |> List.map (headerItemToCell);
      let bodyRows =
        datas
        |> List.map(row(cells))
        |> Array.of_list
        |> ReasonReact.array;

      let header = cells |> header;

      let footer = cells |> footer;
      <table ref=(self.handle(apperTable)) name=tableName>
        <thead> header </thead>
        <tbody> bodyRows </tbody>
        <tfoot> footer </tfoot>
      </table>;
    },
  };
};

type todo = {
  text: string,
  id: string,
};

type todoHeader =
  | ID
  | Name;

module TableSample = {
  let renderRow = (headers, data) => {
    let row =
      headers
      |> List.map(header =>
           switch (header.column) {
           | ID => <td style=(header.style)> <div> (data.id |> ReasonReact.string) </div> </td>
           | Name => <td style=(header.style)> <div> (data.text |> ReasonReact.string) </div> </td>
           }
         )
      |> Array.of_list
      |> ReasonReact.array;
    <tr> row </tr>;
  };
  let renderHeader = headers =>
    <Fragment>
      (
        headers
        |> List.map(header =>
             switch (header.column) {
             | ID => <th> (ReasonReact.string("ID")) </th>
             | Name => <th> (ReasonReact.string("Name")) </th>
             }
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </Fragment>;

  let renderFooter = headers =>
    <Fragment>
      <tr>
        (
          headers
          |> List.map(header =>
               switch (header.column) {
               | ID => <td />
               | Name => <td />
               }
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </tr>
    </Fragment>;
};

module TodoTableDef = {
  type column = todoHeader;
  type relationDataType = todo;
  type header = headerItem(column);
  type cell = tableCell(column);
  let dataRowStyle = (headers, data) => "";
  let headerRowStyle = (headers) => "";
  let footerRowStyle = (headers) => "";
  let defaultHeader = header => {
    switch (header) {
    | ID => {
      column: ID,
      size: Small,
      isSizeFixed: false
      }
    | Name => {
      column: Name,
      size: Large,
      isSizeFixed: false
      }
    };
  }

};

module TodoFlexibleTable = FlexibleTable(TodoTableDef);

let () = {
  let todo = {text: "", id: "id"};
  let el =
    <TodoFlexibleTable
      tableName="todoTable"
      datas=[todo]
      headerItems=(TodoFlexibleTable.defaultHeaders([ID, Name]))
      row=TableSample.renderRow
      footer=TableSample.renderFooter
      header=TableSample.renderHeader
    />;
  ();
};
