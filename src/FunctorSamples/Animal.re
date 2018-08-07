open Cat;
open Dog;

type animalCharacter =
  | Cat(cat)
  | Dog(dog);

type animalA = {
  name: string,
  height: float,
  weight: float,
  character: animalCharacter,
};

module ANIMAL = {
  type a = pri {name: string};

  type b = pri | B | BB;
};

type huu = {name: string};
