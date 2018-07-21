
type result('v, 'e) = Success('v) | Failure('e);

module type PromiseWrapperDef = {
  type v;
};
module PromiseWrapper = (D: PromiseWrapperDef) => {
  include Js.Promise;

  type action = 
    | Completed(D.v)
    | Error(Js.Promise.error);

  type state = option(result(D.v, Js.Promise.error));

  let component = ReasonReact.reducerComponent("PromiseWrapper");

  let make = (
    ~promise: Js.Promise.t(D.v),
    ~whenSuccess: 'v => ReasonReact.reactElement, 
    ~whenError, 
    ~whenPending, 
    _children
    ) => {
    ...component,
    initialState: () => None,
    reducer: (action, _) => 
      switch (action) {
      | Completed(value) => 
        let state = Some(Success(value));
        ReasonReact.Update(state)
      | Error(e) => 
        let state = Some(Failure(e));
        ReasonReact.Update(state)
      }
    ,
    didMount: (self) => {
        promise
          |> then_(value => resolve(self.send(Completed(value))))
          |> catch(error => resolve(self.send(Error(error))))
          |> ignore
    },
    render: (self) => {
      switch (self.state) {
      | None => whenPending
      | Some(result) => 
        switch (result) {
        | Success(value) => whenSuccess(value)
        | Failure(e) => whenError(e)
        };
      };
    }
  };
}