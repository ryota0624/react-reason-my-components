module type Animal = {
  type t;
  let weight: t => float;
  let height: t => float;
  let groupName: string; 
};

type animal = {
  weight: float,
  height: float,
}