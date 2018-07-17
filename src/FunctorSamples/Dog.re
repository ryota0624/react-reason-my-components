open Animal;
open AnimalBook;

type dog = animal({
  .
  height: float,
  weight: float,
  getLabel: unit => string,
  pattern: int,
});

let make = (~height: float, ~weight:float, ~pattern:int):dog => {
  pub height = height;
  pub weight = weight;
  pub getLabel = (_) => {|
    $height $weight
    |};
  pub pattern = pattern;
};


module Dog = {
  type t = dog;
  let height = t => t#height;
  let weight = t => t#weight;
  let groupName = "Dog"
}

module DogBook = AnimalBook(Dog);


