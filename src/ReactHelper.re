let option = op => switch (op) {
| Some(a) => a
| None => ReasonReact.null
};

let optionalHandler = op => switch (op) {
  | Some(fn) => fn () 
  | None => ()
};