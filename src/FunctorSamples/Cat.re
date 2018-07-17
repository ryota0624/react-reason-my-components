open Animal;

type cat = {
  height: float,
  weight: float,
  pattern: int,
};

type animal +=
  | Cat(cat);

module CatFun = {
  type t = cat;
  let make = cat => Cat(cat);
  let height = t =>
    switch (t) {
    | Cat(cat) => cat.height
    };
  let weight = t =>
    switch (t) {
    | Cat(cat) => cat.height
    };
  let groupName = "Cat";
};

let c = CatFun.make({weight: 100.0, height: 100.0, pattern: 1});