module type Animal = {
  type t;
  let weight: t => float;
  let height: t => float;
  let groupName: string; 
};

[@bs.deriving abstract]
type animal('d) = {
  ..
  weight: float,
  height: float,
} as 'd;