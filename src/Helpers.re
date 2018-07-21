module Option = {
  let withDefault = (default, op) =>
    switch (op) {
    | Some(value) => value
    | None => default
    };
};

module String = {
  let contain = (target: string, search: string) => {
    open Js.Re;
    test(target, fromString(search))
  }
}