module type TableDefine = {
  type rowDataType;
  type headerType;
  let renderHeader: headerType => ReasonReact.reactElement;
  let render: list(headerType) => rowDataType => ReasonReact.reactElement;
};

let component = ReasonReact.statelessComponent("FlexibleTable");

module Table = (T: TableDefine) => {
  let make = (~tableName: string, ~datas: list(T.rowDataType), ~headers: list(T.headerType), _chiildren) => {
    ...component,
    render: _ => {
      let bodyRows =
        datas |> List.map(T.render(headers)) |> Array.of_list |> ReasonReact.array;
      let headerRow =
        headers |> List.map(T.renderHeader) |> Array.of_list |> ReasonReact.array;
      <table name=tableName> <thead> <tr> (headerRow) </tr> </thead> <tbody> bodyRows </tbody> </table>;
    },
  };
};

type todo = {
  text: string,
   id: string
  };

type todoHeader = ID | Name;  

module TableSample = {

  module TodoTableDefine = {
    type rowDataType = todo;
    type headerType = todoHeader;
    let render = headers => data => {
      let row = headers 
        |> List.map (header => 
            switch (header) {
              | ID => <td><div>
                (data.id |> ReasonReact.string)
                </div></td>
              | Name => <td><div>
                (data.text |> ReasonReact.string)
                </div></td> 
            })
        |> Array.of_list |> ReasonReact.array;
      <tr> (row) </tr>
    }
    let renderHeader = header => {
      switch (header) {
      | ID => <th>(ReasonReact.string("ID"))</th>
      | Name => <th>(ReasonReact.string("Name"))</th> 
      };
    }
  };
  
  module TodoTable = Table(TodoTableDefine);
}


let () = {
  let todo = {text: "", id: "id"};
  let el = <TableSample.TodoTable tableName="todoTable" datas=([todo]) headers=[ID, Name]/>;
}
