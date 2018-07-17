module Manager = {
  type t('action, 'state) = {
    mutable state: 'state,
    reducer: ('action, 'state) => ('state, list(Js.Promise.t('action))),
    mutable listeners: list(unit => unit),
    mutable errorListeners: list(Js.Promise.error => unit),
  };
  let unsubscribe = (store, listener, ()) =>
    store.listeners = List.filter(l => listener !== l, store.listeners);

  let subscribe = (store, listener) => {
    store.listeners = [listener, ...store.listeners];
    unsubscribe(store, listener);
  };

  let getState = store => store.state;

  let unsubscribeError = (store, listener, ()) =>
    store.errorListeners =
      List.filter(l => listener !== l, store.errorListeners);

  let subscribeError = (store, listener) => {
    store.errorListeners = [listener, ...store.errorListeners];
    unsubscribeError(store, listener);
  };

  let make = (reducer, initialState) => {
    reducer,
    state: initialState,
    listeners: [],
    errorListeners: [],
  };

  let rec dispatch = (store, action) => {
    let (updatedState, actionPromises) = store.reducer(action, store.state);
    store.state = updatedState;
    List.iter(listener => listener(), store.listeners);
    actionPromises
    |> List.iter(actionPromise =>
         actionPromise
         |> Js.Promise.then_(wrapAction => {
              dispatch(store, wrapAction);
              Js.Promise.resolve();
            })
         |> Js.Promise.catch(error => {
              List.iter(listener => listener(error), store.errorListeners);
              Js.Promise.resolve();
            })
         |> ignore
       );
    ();
  };
};

type action =
  | Increment
  | Decrement;

type state = {
  value: int,
  label: string,
};

let reducer = (action: action, state: state) =>
  switch (action) {
  | Increment =>
    let nextValue = state.value + 1;
    (
      {...state, value: nextValue},
      if (nextValue < 100) {
        [Js.Promise.resolve(Increment)];
      } else {
        [];
      },
    );
  | Decrement => ({...state, value: state.value - 1}, [])
  };

let () = {
  let manager = Manager.make(reducer, {value: 0, label: "_"});

  let _ =
    Manager.subscribe(manager, () =>
      Js.Console.log(Manager.getState(manager))
    );
  Manager.dispatch(manager, Increment);
};
