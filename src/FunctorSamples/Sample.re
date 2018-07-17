open Animal;
open Dog;
open Cat;

let showAnimalSizeText = animal =>
  switch (animal) {
  | Dog(dog) => DogFun.height(animal)
  | Cat(cat) => CatFun.height(animal)
  };

Js.Console.log(showAnimalSizeText(d));
Js.Console.log(showAnimalSizeText(c));
