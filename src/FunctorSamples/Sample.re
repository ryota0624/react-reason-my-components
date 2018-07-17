open Animal;
open Dog;
open Cat;

type animalType = Cat(animal, cat) | Dog(animal, dog);


type c = D;

let showAnimalSizeText = (animalType) => {
   let Cat(animal, _) | Dog(animal, _) = animalType;
   animal.weight
}

