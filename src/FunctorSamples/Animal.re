type animal = ..;

module type Animal = {
  type t;
  let make: t => animal;
  let getAnimal: animal => t;
  let weight: animal => float;
  let height: animal => float;
  let groupName: string;
};
