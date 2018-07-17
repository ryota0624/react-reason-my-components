open Animal;

[@bs.deriving abstract]
type cat = {
  height: float,
  weight: float,
  pattern: int,
};

module Cat = {
  type t = cat;
  let height = t => t |. heightGet;
  let weight = t => t |. weightGet;
  let groupName = "Cat"
}

let c = cat(~weight=100.0, ~height=100.0, ~pattern=1);

module CatBook = AnimalBook.AnimalBook(Cat);