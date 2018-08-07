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

let (==>) = (a, b) => (a, b);

type appRoute =
  | Home(int)
  | About(string)
  | NotFound;

module type GlobalStore = {
  type action;
  type state;
  let store: GlobalStateManagement.Manager.t(action, state);

  let renderWithStore:
    (
      ~render: GlobalStateManagement.Manager.t(action, state) =>
               ReasonReact.reactElement
    ) =>
    ReasonReact.reactElement;
};

module type HomeExternalService = {let fetchDataHome: string => string;};

module type AboutExternalService = {let fetchDataAbout: string => string;};

module HomeExternalServiceImpl: HomeExternalService = {
  let fetchDataHome = str => str ++ "!";
};

module AboutExternalServiceImpl: AboutExternalService = {
  let fetchDataAbout = str => str ++ "!";
};

module type AllExternalSercice = {
  include HomeExternalService;
  include AboutExternalService;
};

module AllExternalSerciceImpl: AllExternalSercice = {
  include HomeExternalServiceImpl;
  include AboutExternalServiceImpl;
};

module StateManagementDef = {
  type error = {messages: list(string)};
  type notification = {messages: list(string)};
  type action =
    | DetectedError(error)
    | RefreshError;

  type state = {
    error: option(error),
    notification: option(notification),
  };
};

module MakeHomeContainer =
       (Store: GlobalStore, HomeExternalService: HomeExternalService) => {
  let component = ReasonReact.statelessComponent("MakeHomeContainer");
  let make = (~number, _children) => {
    ...component,
    render: _ =>
      <div>
        <div> (number |> string_of_int |> ReasonReact.string) </div>
        (ReasonReact.string(HomeExternalService.fetchDataHome("HOME")))
      </div>,
  };
};

module AboutContainer = {
  let component = ReasonReact.statelessComponent("AboutContainer");
  let make =
      (
        ~string,
        ~store:
           GlobalStateManagement.Manager.t(
             StateManagementDef.action,
             StateManagementDef.state,
           ),
        _children,
      ) => {
    ...component,
    render: _ => {
      let globalState = GlobalStateManagement.Manager.getState(store);
      <div> <div> (string |> ReasonReact.string) </div> </div>;
    },
  };
};

module MainContentRouting =
       (
         Store:
           GlobalStore with type action = StateManagementDef.action with
             type state = StateManagementDef.state,
         Service: AllExternalSercice,
       )
       : Routing.Routing => {
  module HomePage = MakeHomeContainer(Store, Service);

  let intOfStringOpt = str =>
    try (Some(int_of_string(str))) {
    | Failure(_) => None
    };
  type route = appRoute;
  let urlToRoute = (url: ReasonReact.Router.url, queryParam) =>
    switch (url.path) {
    | ["src", "index.html"] =>
      Home(
        queryParam
        |> Belt.Map.String.get(_, "name")
        |> Belt.Option.flatMap(_, intOfStringOpt)
        |> Belt.Option.getWithDefault(_, 0),
      )
    | ["about"] =>
      About(Belt.Map.String.getWithDefault(queryParam, "name", "default!"))
    | route =>
      Js.Console.log(route);
      NotFound;
    };
  let transition = route =>
    switch (route) {
    | Home(number) =>
      Utils.timePromise(3000)
      |> Js.Promise.then_(_ => <HomePage number /> |> Js.Promise.resolve)
    | About(name) =>
      Store.renderWithStore(~render=store =>
        <AboutContainer string=(Service.fetchDataAbout(name)) store />
      )
      |> Js.Promise.resolve
    | NotFound =>
      <div> (ReasonReact.string("NF")) </div> |> Js.Promise.resolve
    };
};

module App = {
  include StateManagementDef;

  let initialState = {error: None, notification: None};

  let reducer = (action: action, state: state) =>
    switch (action) {
    | DetectedError(error) => {...state, error: Some(error)} ==> []
    | RefreshError => {...state, error: None} ==> []
    };

  let store = GlobalStateManagement.Manager.make(reducer, initialState);

  let renderWithStore = (~render) => render(store);
};

let showErrorModal = (error: App.error, refreshError) =>
  <div>
    (
      error.messages
      |> List.map(ReasonReact.string)
      |> Array.of_list
      |> ReasonReact.array
    )
    <div onClick=(_ => refreshError()) />
  </div>;

let header = () => <div> (ReasonReact.string("IAM HEADER")) </div>;

module AppRoot = (MainContent: Routing.Content) => {
  open ReactHelper;
  let blankPage = <div className="loading" />;
  let component = ReasonReact.statelessComponent("AppRoot");
  let make = (~store, _children) => {
    ...component,
    render: _ =>
      <Fragment>
        (header())
        <MainContent
          initialPage=blankPage
          onError=(
            _ => {
              let error: App.error = {messages: ["PagePrepareError"]};
              GlobalStateManagement.Manager.dispatch(
                store,
                App.DetectedError(error),
              );
            }
          )
          onStartTransition=(() => Js.Console.log("start_transition"))
          onFinishTransition=(() => Js.Console.log("finish_transition"))
        />
      </Fragment>,
  };
};

module AppRootImpl =
  AppRoot(
    (Routing.Application((MainContentRouting(App, AllExternalSerciceImpl)))),
  );

let render = () =>
  ReactDOMRe.renderToElementWithId(<AppRootImpl store=App.store />, "index");

let _ =
  () => {
    let _ = GlobalStateManagement.Manager.subscribe(App.store, render);
    render();
  };
