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
    | LoadedPage(ReasonReact.reactElement);

  let component = ReasonReact.reducerComponent("application");

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
      open Js.Promise;

      let id =
        ReasonReact.Router.watchUrl(url => {
          let route = R.urlToRoute(url);
          self.send(StartPageLoading(getPageElement(self.state.page)));
          R.transition(route)
          |> then_(element => LoadedPage(element) |> self.send |> resolve)
          |> catch(_ => {
               let _: unit = onError();
               resolve();
             })
          |> ignore;
        });

      self.onUnmount(() => ReasonReact.Router.unwatchUrl(id));

      /**
       * TODO 関数化
       */
      self.send(StartPageLoading(getPageElement(self.state.page)));

      R.transition(
        R.urlToRoute(ReasonReact.Router.dangerouslyGetInitialUrl()),
      )
      |> then_(element => LoadedPage(element) |> self.send |> resolve)
      |> catch(_ => {
           let _: unit = onError();
           resolve();
         })
      |> ignore;
    },
    reducer: (action, _) =>
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
      },
    render: self => getPageElement(self.state.page),
  };
};
