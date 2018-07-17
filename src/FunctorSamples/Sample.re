open Animal;

/* type animalType = Cat(cat) | Dog(dog); */


let showAnimalSizeText = (animalType) => {
  /* let Cat(animal) | Dog(animal) = animalType; */

  Js.Console.log(animalType#getLabel());
}

let catText = showAnimalSizeText(Dog.make(~height = 100.0, ~weight = 10.0 , ~pattern = 3));