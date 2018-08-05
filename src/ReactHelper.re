let option = op =>
  switch (op) {
  | Some(a) => a
  | None => ReasonReact.null
  };

let andThen = (a, b, v) => b(a(v)); 
let (>>) = andThen;

let optionalHandler = op =>
  switch (op) {
  | Some(fn) => fn()
  | None => ()
  };

module Fragment = {
  [@bs.module "react"] external fragment : ReasonReact.reactClass = "Fragment";
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=fragment,
      ~props=Js.Obj.empty(),
      children,
    );
};


module Router = {
  let queryParamStrToTuple = (str: string): option((string, string)) => {
    switch (Js.String.split("=", str)) {
    | [|key, value|] => Some((key, value))
    | _ => None
    }
  };

  let optionToArray = (op) => switch (op) {
  | Some(v) => [|v|]
  | None => [||]
  };

  let mapFromArray = pairArray => {
    pairArray
      |> Belt.Map.String.fromArray
  };
  let routeToqueryParamMap = (route: ReasonReact.Router.url) => {
    route.search 
      |> Js.String.split("&")
      |> Array.map(queryParamStrToTuple >> optionToArray)
      |> Belt.Array.concatMany
      |> mapFromArray
  };
}