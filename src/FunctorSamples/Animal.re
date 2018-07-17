open Cat;
open Dog;

type animalCharacter = Cat(cat) | Dog(dog);

type animalA = {
  name: string,
  height: float,
  weight: float,
  character: animalCharacter
}