type headerColumnSize =
  | Small
  | Medium
  | Large
  | Free(float);

let getWidthSize = size =>
  switch (size) {
  | Small => 7.0
  | Medium => 9.5
  | Large => 12.0
  | Free(size) => size
  };

type reportHeaderItemColumn =
  | A
  | B
  | C
  | D
  | E
  | F;

let reportHeaderItemWidthDefaultSize = item =>
  switch (item) {
  | A => Small
  | B => Small
  | C => Small
  | D => Medium
  | E => Small
  | F => Free(10.0)
  };

type headerItemColumn =
  | Id
  | Name
  | Age
  | Gender
  | Report(reportHeaderItemColumn);

let headerItemWidthDefaultSize = item =>
  switch (item) {
  | Id => Small
  | Name => Large
  | Age => Small
  | Gender => Small
  | Report(rhI) => reportHeaderItemWidthDefaultSize(rhI)
  };

[@bs.deriving jsConverter]
type headerItem = {
  column: headerItemColumn,
  size: headerColumnSize,
  isSizeFiexed: bool,
};

let getHeaderItemWidthSize = headerItem => headerItem.size |> getWidthSize;

let headerItemFromAny = headerItem =>
  headerItem |> headerItemToJs |> Obj.magic |> Js.Json.stringify;
let anyToHeaderItem = anyString =>
  anyString |> Js.Json.parseExn |> Obj.magic |> headerItemFromJs;

let valueToString = (func, value) =>
  value |> func |> Obj.magic |> Js.Json.stringify;
let stringFromValue = (func, anyString) =>
  anyString |> Js.Json.parseExn |> Obj.magic |> func;

type header = list(headerItem);
let getWidthSizeByTableWidthSize = (tableWidthSize, header) => {
  let headerSizeList = header |> List.map(getHeaderItemWidthSize);
  let totalHeaderSize = headerSizeList |> List.fold_left((+.), 0.0);
  if (tableWidthSize > totalHeaderSize) {
    let flexibleSizeHeaderCount =
      header
      |> List.filter(header => ! header.isSizeFiexed)
      |> List.length
      |> float_of_int;

    let totalSizeFiexedWidth =
      header
      |> List.filter(header => header.isSizeFiexed)
      |> List.map(getHeaderItemWidthSize)
      |> List.fold_left((+.), 0.0);

    let headerSize =
      (tableWidthSize -. totalSizeFiexedWidth) /. flexibleSizeHeaderCount;
    header |> List.map(headerItem => {...headerItem, size: Free(headerSize)});
  } else {
    header;
  };
};

Js.Console.log(
  {column: Name, size: Free(100.0), isSizeFiexed: false}
  |> valueToString(headerItemToJs)
  |> stringFromValue(headerItemFromJs)
  |> (item => [item])
  |> getWidthSizeByTableWidthSize(1000.0),
);

let () = {
  let v =
    {column: Name, size: Free(100.0), isSizeFiexed: false}
    |> valueToString(headerItemToJs)
    |> stringFromValue(headerItemFromJs);

  Js.Console.log(v.size |> getWidthSize);
};
