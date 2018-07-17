module Fragment = {
  [@bs.module "react"] external fragment : ReasonReact.reactClass = "Fragment";
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=fragment,
      ~props=Js.Obj.empty(),
      children,
    );
};

let component = ReasonReact.statelessComponent("FlexibleTable");

module Table = {
  let make =
      (
        ~datas: list('data),
        ~headerColumns: list('headerColumn),
        ~row: (list('headerColumn), 'data) => ReasonReact.reactElement,
        ~header: list('headerColumn) => ReasonReact.reactElement,
        ~footer: list('headerColumn) => ReasonReact.reactElement,
        ~tableName: string,
        _chiildren,
      ) => {
    ...component,
    render: _ => {
      let bodyRows =
        datas
        |> List.map(row(headerColumns))
        |> Array.of_list
        |> ReasonReact.array;

      let header = headerColumns |> header;

      let footer = headerColumns |> footer;
      <table name=tableName>
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
           switch (header) {
           | ID => <td> <div> (data.id |> ReasonReact.string) </div> </td>
           | Name => <td> <div> (data.text |> ReasonReact.string) </div> </td>
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
             switch (header) {
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
               switch (header) {
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

let () = {
  let todo = {text: "", id: "id"};
  let el =
    <Table
      tableName="todoTable"
      datas=[todo]
      headerColumns=[ID, Name]
      row=TableSample.renderRow
      footer=TableSample.renderFooter
      header=TableSample.renderHeader
    />;
  ();
};
