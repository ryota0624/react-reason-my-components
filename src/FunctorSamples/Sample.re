open Animal;
open Dog;
open Cat;

let showAnimalCharacterInfo = animal =>
  switch (animal) {
  | Dog(dog) => dog.skill
  | Cat(cat) => cat.pattern |> string_of_int
  };

let showAnimalHeight = animal => animal.height;  
