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

  let make =
      (
        _children,
        ~initialPage,
        ~onError,
        ~onStartTransition,
        ~onFinishTransition,
      ) => {
        let transition2 = (url, {ReasonReact.send, ReasonReact.state}) => {
          open Js.Promise;
          let route = R.urlToRoute(url);
          send(StartPageLoading(getPageElement(state.page)));
          R.transition(route)
          |> then_(element => LoadedPage(element) |> send |> resolve)
          |> catch(error => {
               send(DetectedPageLoadError(error));
               resolve();
             })
          |> ignore;
        };
        {
        ...component,
        initialState: () => {page: Loaded(initialPage)},
        didMount: self => {
          let id =
            ReasonReact.Router.watchUrl(self.handle(transition2));
          self.onUnmount(() => ReasonReact.Router.unwatchUrl(id));
          self.handle(transition2)(ReasonReact.Router.dangerouslyGetInitialUrl());
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
    }
};
