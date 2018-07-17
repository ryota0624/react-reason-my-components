open Animal;

/* type animalType = Cat(cat) | Dog(dog); */


let showAnimalSizeText = (animalType) => {
  /* let Cat(animal) | Dog(animal) = animalType; */

  Js.Console.log(animalType |. Cat.heightGet);
}

let catText = showAnimalSizeText(Cat.c);