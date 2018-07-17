open Animal;
open AnimalBook;

type dog = {
  height: float,
  weight: float,
  pattern: int,
};



module Dog = {
  type t = dog;
  let height = t => t.height;
  let weight = t => t.weight;
  let groupName = "Dog"
}

module DogBook = AnimalBook(Dog);


