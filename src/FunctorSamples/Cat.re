open Animal;

type cat = {
  height: float,
  weight: float,
  pattern: int,
};


module Cat = {
  type t = cat;
  let height = t => t.height;
  let weight = t => t.weight;
  let groupName = "Cat"
}

let c:cat = { weight: 100.0, height: 100.0, pattern: 1 };

module CatBook = AnimalBook.AnimalBook(Cat);