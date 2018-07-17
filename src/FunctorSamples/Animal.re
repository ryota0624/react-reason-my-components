module type Animal = {
  type t;
  let weight: t => float;
  let height: t => float;
  let groupName: string; 
};

type animal('d) = {
  ..
  weight: float,
  height: float,
  getLabel: (unit) => string,
} as 'd;