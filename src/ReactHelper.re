let option = op =>
  switch (op) {
  | Some(a) => a
  | None => ReasonReact.null
  };

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
  