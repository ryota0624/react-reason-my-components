open ReportHeader;

type reportHeaderItemColumn('t) +=
  Id
  | Name
  | Author
  | CreatedAt;

Js.Console.log(
  {column: CreatedAt, size: Free(1500.0), isSizeFiexed: false}
  |> valueToString(headerItemToJs)
  |> stringFromValue(headerItemFromJs)
  |> (item => [item])
  |> getWidthSizeByTableWidthSize(1000.0),
);
