open ReportHeader;

type headerTag =
  | UserHeader;
type reportHeaderItemColumn('headerTag) +=
  | Id
  | Name
  | Age
  | Gender;
