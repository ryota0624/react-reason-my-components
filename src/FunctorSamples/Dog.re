open Animal;
type dog = {
  height: float,
  weight: float,
  pattern: int,
};

type animal +=
  | Dog(dog);

module DogFun = {
  type t = dog;
  let make = dog => Dog(dog);
  let height = t =>
    switch (t) {
    | Dog(dog) => dog.height
    };
  let weight = t =>
    switch (t) {
    | Dog(dog) => dog.height
    };
  let groupName = "Dog";
};

let d = DogFun.make({weight: 500.0, height: 500.0, pattern: 1});