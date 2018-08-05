module type Routing_ = {
  type route;
  let urlToRoute: ReasonReact.Router.url => route;
  let transition: route => Js.Promise.t(ReasonReact.reactElement);
};

module type Routing= {
  type route;
  let urlToRoute: (ReasonReact.Router.url, Belt.Map.String.t(string)) => route;
  let transition: route => Js.Promise.t(ReasonReact.reactElement);
};

module type Content = {
  type page;

  type state;

  type action;

  let make: ('a, ~initialPage: ReasonReact.reactElement,
  ~onError: Js.Promise.error => unit, ~onStartTransition: unit => unit,
  ~onFinishTransition: unit => unit) =>
  ReasonReact.componentSpec(state, state, ReasonReact.noRetainedProps,
                             ReasonReact.noRetainedProps, action)
};

module Application = (R: Routing): Content => {
  type page =
    | InTransition(ReasonReact.reactElement)
    | Loaded(ReasonReact.reactElement);

  let getPageElement = page => {
    let InTransition(pageElement) | Loaded(pageElement) = page;
    pageElement;
  };

  type state = {page, lastTransitionTime: float};

  type action =
    | StartPageLoading(ReasonReact.reactElement, float)
    | LoadedPage(ReasonReact.reactElement, float)
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
    let transition = (url, {ReasonReact.send, ReasonReact.state}) => {
      open Js.Promise;
      let startTransitionTime = Js.Date.now();
      let route = R.urlToRoute(url, ReactHelper.Router.routeToqueryParamMap(url));
      send(StartPageLoading(getPageElement(state.page), startTransitionTime));
      R.transition(route)
      |> then_(element => LoadedPage(element, startTransitionTime) |> send |> resolve)
      |> catch(error => {
           send(DetectedPageLoadError(error));
           resolve();
         })
      |> ignore;
    };
    {
      ...component,
      initialState: () => {page: Loaded(initialPage), lastTransitionTime: Js.Date.now()},
      didMount: self => {
        let id = ReasonReact.Router.watchUrl(self.handle(transition));
        self.onUnmount(() => ReasonReact.Router.unwatchUrl(id));
        self.handle(
          transition,
          ReasonReact.Router.dangerouslyGetInitialUrl(),
        );
      },
      reducer: (action, state) =>
        switch (action) {
        | StartPageLoading(element, transitionStartTime) =>
          ReasonReact.UpdateWithSideEffects(
            {page: InTransition(element), lastTransitionTime: transitionStartTime},
            (_ => onStartTransition()),
          )
        | LoadedPage(element, transitionStartTime) =>
          if (transitionStartTime == state.lastTransitionTime) {
            ReasonReact.UpdateWithSideEffects(
              {...state, page: Loaded(element)},
              (_ => onFinishTransition()),
            )
          } else ReasonReact.NoUpdate
        | DetectedPageLoadError(error) =>
          ReasonReact.UpdateWithSideEffects(
            {...state, page: Loaded(getPageElement(state.page))},
            (_ => onError(error)),
          )
        },
      render: self => getPageElement(self.state.page),
    };
  };
};
