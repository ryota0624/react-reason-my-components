module type Routing = {
  type route;
  let urlToRoute: ReasonReact.Router.url => route;
  let transition: route => Js.Promise.t(ReasonReact.reactElement);
};

module Application = (R: Routing) => {
  type page =
    | InTransition(ReasonReact.reactElement)
    | Loaded(ReasonReact.reactElement);

  let getPageElement = page => {
    let InTransition(pageElement) | Loaded(pageElement) = page;
    pageElement;
  };

  type state = {page};

  type action =
    | StartPageLoading(ReasonReact.reactElement)
    | LoadedPage(ReasonReact.reactElement)
    | DetectedPageLoadError(Js.Promise.error);

  let component = ReasonReact.reducerComponent("application");

  let transition = (send, page, url) => {
    open Js.Promise;
    let route = R.urlToRoute(url);
    send(StartPageLoading(getPageElement(page)));
    R.transition(route)
    |> then_(element => LoadedPage(element) |> send |> resolve)
    |> catch(error => {
         send(DetectedPageLoadError(error));
         resolve();
       })
    |> ignore;
  };
  let make =
      (
        _children,
        ~initialPage,
        ~onError,
        ~onStartTransition,
        ~onFinishTransition,
      ) => {
    ...component,
    initialState: () => {page: Loaded(initialPage)},
    didMount: self => {

      let id =
        ReasonReact.Router.watchUrl(transition(self.send, self.state.page));

      self.onUnmount(() => ReasonReact.Router.unwatchUrl(id));

      transition(self.send, self.state.page, ReasonReact.Router.dangerouslyGetInitialUrl())
    },
    reducer: (action, state) =>
      switch (action) {
      | StartPageLoading(element) =>
        ReasonReact.UpdateWithSideEffects(
          {page: InTransition(element)},
          (_ => onStartTransition()),
        )
      | LoadedPage(element) =>
        ReasonReact.UpdateWithSideEffects(
          {page: Loaded(element)},
          (_ => onFinishTransition()),
        )
      | DetectedPageLoadError(error) =>
        ReasonReact.UpdateWithSideEffects(
            {page: Loaded(getPageElement(state.page))},
            (_ => onError(error)))
      },
    render: self => getPageElement(self.state.page),
  };
};
