type headerColumnSize = Small | Medium | Large | Free(float);

let getWidthSize = size => {
  switch size {
  | Small => 7.0
  | Medium => 9.5
  | Large => 12.0
  | Free(size) => size
  };
}

type reportHeaderItemColumn = A | B | C | D | E | F;

let reportHeaderItemWidthDefaultSize = (item) => switch (item) {
| A => Small
| B => Small
| C => Small
| D => Medium
| E => Small
| F => Free(10.0)
};

type headerItemColumn = Id | Name | Age | Gender | Report(reportHeaderItemColumn);

let headerItemWidthDefaultSize = (item) => switch item {
| Id => Small
| Name => Large
| Age => Small
| Gender => Small
| Report(rhI) => reportHeaderItemWidthDefaultSize(rhI)
};

type headerItem = {
    column: headerItemColumn,
    mutable size: headerColumnSize,
    isSizeFiexed: bool
  };

let getHeaderItemWidthSize = headerItem => headerItem.size |> getWidthSize;

type header = list(headerItem);

let getWidthSizeByTableWidthSize = (tableWidthSize, header) => {
  let headerSizeList= header |> List.map(getHeaderItemWidthSize);
  let totalHeaderSize = headerSizeList |> List.fold_left((+.), 0.0);
  if (tableWidthSize < totalHeaderSize) {
    let flexibleSizeHeaderCount = header |> List.filter(header => !header.isSizeFiexed) |> List.length |> float_of_int;
    let totalSizeFiexedWidth = header 
      |> List.filter(header => header.isSizeFiexed) 
      |> List.map(getHeaderItemWidthSize)
      |> List.fold_left((+.), 0.0);

    let headerSize = (tableWidthSize -. totalSizeFiexedWidth) /. flexibleSizeHeaderCount;
    header |> List.map (headerItem => {
      headerItem.size = Free(headerSize);
      headerItem;
    })
  } else {
    header;
  }
}