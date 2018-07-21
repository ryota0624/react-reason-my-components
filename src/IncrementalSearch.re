open Helpers;

module type Def = {
  type entity;
  let findEntities: string => Js.Promise.t(list(entity));
};

module IncrementalSearch = (D: Def) => {
  include Js.Promise;
  type action =
    | InputText(string)
    | CompletedFindEntities(list(D.entity))
    | Dequeue;

  type state = {
    text: string,
    entities: list(D.entity),
    queueGetEntitesCommand: list(string),
  };

  let component = ReasonReact.reducerComponent("IncrementalSearch");

  let onInputText = (e, {ReasonReact.send}) => {
    let text = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value;
    send(InputText(text));
  };

  let make =
      (
        ~defaultText: option(string)=?,
        ~searchDelay: option(float)=?,
        ~searchResultView: list(D.entity) => ReasonReact.reactElement, 
        _children,
      ) => {
    ...component,
    initialState: () => {
      text: Option.withDefault("", defaultText),
      entities: [],
      queueGetEntitesCommand: [],
    },
    didMount: (self) => {
      self.send(InputText(self.state.text))
    },
    reducer: (action, state) =>
      {
        switch (action) {
        | InputText(text) =>
          let delay = Option.withDefault(0.0, searchDelay);
          ReasonReact.UpdateWithSideEffects(
            {...state, text: text, queueGetEntitesCommand: List.concat([state.queueGetEntitesCommand, [text]])},
            (
              self => {
                let _ = Js.Global.setTimeout(() => self.send(Dequeue), delay |> floor |> int_of_float);
                ();
              }
            ),
          );
        | CompletedFindEntities(entities) =>
          ReasonReact.Update({...state, entities})
        | Dequeue =>
          switch (state.queueGetEntitesCommand) {
          | [command] =>
            ReasonReact.UpdateWithSideEffects(
              {...state, queueGetEntitesCommand: []},
              (
                self =>
                  D.findEntities(command)
                  |> then_(entities =>
                      resolve(self.send(CompletedFindEntities(entities)))
                    )
                  |> ignore
              ),
            )
          | [_, ...tail] =>
            ReasonReact.Update({...state, queueGetEntitesCommand: tail})
          | [] => ReasonReact.NoUpdate
          }
        }
      },
    render: self => {
      let text = self.state.text;
      <div>
        <input
          onInput=(self.handle(onInputText))
          value=(text)
        />
        (searchResultView(self.state.entities))
      </div>;
    },
  };
};
