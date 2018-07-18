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

[@bs.deriving jsConverter]
type headerItem('t) = {
  column: 't,
  size: headerColumnSize,
  isSizeFixed: bool,
};

let valueToString = (func, value) =>
  value |> func |> Obj.magic |> Js.Json.stringify;
let stringFromValue = (func, anyString) =>
  anyString |> Js.Json.parseExn |> Obj.magic |> func;

type header('t) = list(headerItem('t));
let getWidthSizeByTableWidthSize = (tableWidthSize, header) => {
  let getHeaderItemWidthSize = headerItem => headerItem.size |> getWidthSize;
  let headerSizeList = header |> List.map(getHeaderItemWidthSize);
  let totalHeaderSize = headerSizeList |> List.fold_left((+.), 0.0);
  if (tableWidthSize > totalHeaderSize) {
    let flexibleSizeHeaderCount =
      header
      |> List.filter(header => ! header.isSizeFixed)
      |> List.length
      |> float_of_int;

    let totalSizeFiexedWidth =
      header
      |> List.filter(header => header.isSizeFixed)
      |> List.map(getHeaderItemWidthSize)
      |> List.fold_left((+.), 0.0);

    let headerSize =
      (tableWidthSize -. totalSizeFiexedWidth) /. flexibleSizeHeaderCount;
    header |> List.map(headerItem => {...headerItem, size: Free(headerSize)});
  } else if (tableWidthSize == 0.0) {
    header |> List.map(headerItem => {...headerItem, size: Free(0.0)});
  } else {
    header;
  };
};
