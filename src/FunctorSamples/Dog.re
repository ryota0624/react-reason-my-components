open Animal;
open AnimalBook;

[@bs.deriving abstract]
type dog = {
  height: float,
  weight: float,
};


module Dog = {
  type t = dog;
  let height = t => t |. heightGet;
  let weight = t => t |. weightGet;
  let groupName = "Dog"
}

module DogBook = AnimalBook(Dog);