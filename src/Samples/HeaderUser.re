open ReportHeader;

type headerTag =
  | UserHeader;
type reportHeaderItemColumn('headerTag) +=
  | Id
  | Name
  | Age
  | Gender;

Js.Console.log(
  {column: Name, size: Free(1500.0), isSizeFiexed: false}
  |> valueToString(headerItemToJs)
  |> stringFromValue(headerItemFromJs)
  |> (item => [item])
  |> getWidthSizeByTableWidthSize(1000.0),
);
