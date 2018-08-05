module Utils = {
  let timePromise = count =>
  Js.Promise.make((~resolve, ~reject as _) => {
    /* https://bucklescript.github.io/bucklescript/Manual.html#__code_bs_code_for_explicit_uncurried_callback */
    /* (. 引数) で引数をuncurryすることを明示してる */
    /* promiseのここだとよくわからないけど
          Array.mapとか
          Array.map((n) => 1 + n, [4,4])みたいにbsで書くと
          Array.map((n) => 1 + n)([4,4])ってjsになっちゃうからかな？
      */
    let _ = Js.Global.setTimeout(() => resolve(. count), count);
    ();
  });
};

let (==>) = a => b => (a, b)

type appRoute =
  | Home
  | About
  | NotFound;

module type GlobalStore = {
  type action;
  type state;
  let store: GlobalStateManagement.Manager.t(action, state);

  let renderWithStore: (~render: GlobalStateManagement.Manager.t(action, state) => ReasonReact.reactElement) => ReasonReact.reactElement;
};

module StateManagementDef = {
  type error = {
    messages: list(string),
  };
  type notification = {
    messages: list(string),
  }
  type action = 
    | DetectedError(error)
    | RefreshError;

  type state = {
    error: option(error),
    notification: option(notification)
  };
}

module MakeHomeContainer = (Store: GlobalStore) => {
  let component = ReasonReact.statelessComponent("MakeHomeContainer");
  let make = (~number, _children) => {
    ...component,
    render: (_) => {
      <div> (number |> string_of_int |> ReasonReact.string) </div>
    } 
  }
}

module AboutContainer = {
  let component = ReasonReact.statelessComponent("AboutContainer");
  let make = (~string, ~store: GlobalStateManagement.Manager.t(StateManagementDef.action, StateManagementDef.state), _children) => {
    ...component,
    render: (_) => {
      let globalState = GlobalStateManagement.Manager.getState(store);
      <div>
        <div> (string |> ReasonReact.string) </div>
      </div>
    } 
  }
}

module MainContentRouting = (Store: GlobalStore
  with type action = StateManagementDef.action
  with type state = StateManagementDef.state
  ): Routing.Routing => {
  module HomePage = MakeHomeContainer(Store);
  type route = appRoute;
  let urlToRoute = (url: ReasonReact.Router.url) =>
    switch (url.path) {
    | ["src", "index.html"] => Home
    | ["about"] => About
    | route =>
      Js.Console.log(route);
      NotFound;
    };
  let transition = route =>
    switch (route) {
    | Home =>
      Utils.timePromise(3000)
      |> Js.Promise.then_(v =>
           <HomePage number=v />
           |> Js.Promise.resolve
         )
    | About =>
      Store.renderWithStore(~render=store => <AboutContainer string="" store=store/>) 
        |> Js.Promise.resolve
    | NotFound =>
      <div> (ReasonReact.string("NF")) </div> |> Js.Promise.resolve
    };
};


module App {
  include StateManagementDef;

  let initialState = {
    error: None,
    notification: None
  }

  let reducer = (action: action, state: state) =>
    switch (action) {
    | DetectedError(error) => {...state, error: Some(error)} ==> []
    | RefreshError => {...state, error: None} ==> []
    };
  
  let store = GlobalStateManagement.Manager.make(reducer, initialState);

  let renderWithStore = (~render) => {
    render(store)
  }
}


let showErrorModal = (error: App.error, refreshError) => {
  <div>
    (
      error.messages
        |> List.map (ReasonReact.string)
        |> Array.of_list
        |> ReasonReact.array
    )

    <div onClick=((_) => refreshError())/>
  </div>
}

let header = () => {
  <div>
    (ReasonReact.string("IAM HEADER"))
  </div>
}



module AppRoot = {
  include App;
  module MainContent = Routing.Application(MainContentRouting(App));
  let blankPage = <div className="loading"> </div>;
  open ReactHelper;
  let component = ReasonReact.statelessComponent("AppRoot");
  let make = (_children) => {
    ...component,
    render: _ => {
      <Fragment>
        (header())
        <MainContent 
          initialPage={blankPage}
          onError=(_ => {
            let error: error = {messages: ["PagePrepareError"]};
            GlobalStateManagement.Manager.dispatch(store, DetectedError(error))
          })
          onStartTransition=(() => Js.Console.log("start_transition"))
          onFinishTransition=(() => Js.Console.log("finish_transition"))
        />
      </Fragment>
    }
  }

};


let render = () => ReactDOMRe.renderToElementWithId(
  <AppRoot />
  , "index",
);


let _ = () => {
  let _ = GlobalStateManagement.Manager.subscribe(App.store, render);
  render();
};