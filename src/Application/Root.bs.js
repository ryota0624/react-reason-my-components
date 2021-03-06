// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Routing$ReactTemplate = require("../Routing.bs.js");
var Operator$ReactTemplate = require("../Operator.bs.js");
var UrlParser$ReactTemplate = require("../UrlParser.bs.js");
var ReactHelper$ReactTemplate = require("../ReactHelper.bs.js");
var GlobalStateManagement$ReactTemplate = require("../Samples/GlobalStateManagement.bs.js");

function timePromise(count) {
  return new Promise((function (resolve, _) {
                setTimeout((function () {
                        return resolve(count);
                      }), count);
                return /* () */0;
              }));
}

var Utils = /* module */Block.localModule(["timePromise"], [timePromise]);

function $eq$eq$great(a, b) {
  return /* tuple */[
          a,
          b
        ];
}

function fetchDataHome(str) {
  return str + "!";
}

var HomeExternalServiceImpl = /* module */Block.localModule(["fetchDataHome"], [fetchDataHome]);

function fetchDataAbout(str) {
  return str + "!";
}

var AboutExternalServiceImpl = /* module */Block.localModule(["fetchDataAbout"], [fetchDataAbout]);

var AllExternalSerciceImpl = /* module */Block.localModule([
    "fetchDataHome",
    "fetchDataAbout"
  ], [
    fetchDataHome,
    fetchDataAbout
  ]);

function getMessages(param) {
  return param[/* messages */0];
}

var StateManagementDef = /* module */Block.localModule(["getMessages"], [getMessages]);

function MakeHomeContainer(Store) {
  return (function (HomeExternalService) {
      var component = ReasonReact.statelessComponent("HomeContainer");
      var make = function (number, _) {
        return /* record */Block.record([
                  "debugName",
                  "reactClassInternal",
                  "handedOffState",
                  "willReceiveProps",
                  "didMount",
                  "didUpdate",
                  "willUnmount",
                  "willUpdate",
                  "shouldUpdate",
                  "render",
                  "initialState",
                  "retainedProps",
                  "reducer",
                  "subscriptions",
                  "jsElementWrapped"
                ], [
                  component[/* debugName */0],
                  component[/* reactClassInternal */1],
                  component[/* handedOffState */2],
                  component[/* willReceiveProps */3],
                  component[/* didMount */4],
                  component[/* didUpdate */5],
                  component[/* willUnmount */6],
                  component[/* willUpdate */7],
                  component[/* shouldUpdate */8],
                  (function () {
                      var __x = GlobalStateManagement$ReactTemplate.Manager[/* getState */2](Store[/* store */0])[/* notification */1];
                      var __x$1 = Belt_Option.map(__x, (function (param) {
                              return Operator$ReactTemplate.$great$great(getMessages, List.hd, param);
                            }));
                      var notification = Belt_Option.getWithDefault(__x$1, "");
                      return React.createElement("div", undefined, React.createElement("div", undefined, String(number)), React.createElement("div", undefined, notification), Curry._1(HomeExternalService[/* fetchDataHome */0], "HOME"));
                    }),
                  component[/* initialState */10],
                  component[/* retainedProps */11],
                  component[/* reducer */12],
                  component[/* subscriptions */13],
                  component[/* jsElementWrapped */14]
                ]);
      };
      return /* module */Block.localModule([
                "component",
                "make"
              ], [
                component,
                make
              ]);
    });
}

function MakeAboutContainer() {
  return (function () {
      var component = ReasonReact.statelessComponent("AboutContainer");
      var make = function (string, _) {
        return /* record */Block.record([
                  "debugName",
                  "reactClassInternal",
                  "handedOffState",
                  "willReceiveProps",
                  "didMount",
                  "didUpdate",
                  "willUnmount",
                  "willUpdate",
                  "shouldUpdate",
                  "render",
                  "initialState",
                  "retainedProps",
                  "reducer",
                  "subscriptions",
                  "jsElementWrapped"
                ], [
                  component[/* debugName */0],
                  component[/* reactClassInternal */1],
                  component[/* handedOffState */2],
                  component[/* willReceiveProps */3],
                  component[/* didMount */4],
                  component[/* didUpdate */5],
                  component[/* willUnmount */6],
                  component[/* willUpdate */7],
                  component[/* shouldUpdate */8],
                  (function () {
                      return React.createElement("div", undefined, React.createElement("div", undefined, string));
                    }),
                  component[/* initialState */10],
                  component[/* retainedProps */11],
                  component[/* reducer */12],
                  component[/* subscriptions */13],
                  component[/* jsElementWrapped */14]
                ]);
      };
      return /* module */Block.localModule([
                "component",
                "make"
              ], [
                component,
                make
              ]);
    });
}

function MainContentRouting(Store) {
  return (function (Service) {
      var HomeExternalService = [Service[0]];
      var component = ReasonReact.statelessComponent("HomeContainer");
      var make = function (number, _) {
        return /* record */Block.record([
                  "debugName",
                  "reactClassInternal",
                  "handedOffState",
                  "willReceiveProps",
                  "didMount",
                  "didUpdate",
                  "willUnmount",
                  "willUpdate",
                  "shouldUpdate",
                  "render",
                  "initialState",
                  "retainedProps",
                  "reducer",
                  "subscriptions",
                  "jsElementWrapped"
                ], [
                  component[/* debugName */0],
                  component[/* reactClassInternal */1],
                  component[/* handedOffState */2],
                  component[/* willReceiveProps */3],
                  component[/* didMount */4],
                  component[/* didUpdate */5],
                  component[/* willUnmount */6],
                  component[/* willUpdate */7],
                  component[/* shouldUpdate */8],
                  (function () {
                      var __x = GlobalStateManagement$ReactTemplate.Manager[/* getState */2](Store[/* store */0])[/* notification */1];
                      var __x$1 = Belt_Option.map(__x, (function (param) {
                              return Operator$ReactTemplate.$great$great(getMessages, List.hd, param);
                            }));
                      var notification = Belt_Option.getWithDefault(__x$1, "");
                      return React.createElement("div", undefined, React.createElement("div", undefined, String(number)), React.createElement("div", undefined, notification), Curry._1(HomeExternalService[/* fetchDataHome */0], "HOME"));
                    }),
                  component[/* initialState */10],
                  component[/* retainedProps */11],
                  component[/* reducer */12],
                  component[/* subscriptions */13],
                  component[/* jsElementWrapped */14]
                ]);
      };
      var component$1 = ReasonReact.statelessComponent("AboutContainer");
      var make$1 = function (string, _) {
        return /* record */Block.record([
                  "debugName",
                  "reactClassInternal",
                  "handedOffState",
                  "willReceiveProps",
                  "didMount",
                  "didUpdate",
                  "willUnmount",
                  "willUpdate",
                  "shouldUpdate",
                  "render",
                  "initialState",
                  "retainedProps",
                  "reducer",
                  "subscriptions",
                  "jsElementWrapped"
                ], [
                  component$1[/* debugName */0],
                  component$1[/* reactClassInternal */1],
                  component$1[/* handedOffState */2],
                  component$1[/* willReceiveProps */3],
                  component$1[/* didMount */4],
                  component$1[/* didUpdate */5],
                  component$1[/* willUnmount */6],
                  component$1[/* willUpdate */7],
                  component$1[/* shouldUpdate */8],
                  (function () {
                      return React.createElement("div", undefined, React.createElement("div", undefined, string));
                    }),
                  component$1[/* initialState */10],
                  component$1[/* retainedProps */11],
                  component$1[/* reducer */12],
                  component$1[/* subscriptions */13],
                  component$1[/* jsElementWrapped */14]
                ]);
      };
      var homeRoute = UrlParser$ReactTemplate.toRoute((function (intValue) {
              return /* Home */Block.variant("Home", 0, [intValue]);
            }), UrlParser$ReactTemplate.$pipe$unknown(UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.top, UrlParser$ReactTemplate.s("src")), UrlParser$ReactTemplate.s("index.html")), UrlParser$ReactTemplate.intParamWithDefault("name", 0)));
      var aboutRoute = UrlParser$ReactTemplate.toRoute((function (str) {
              return /* About */Block.variant("About", 1, [str]);
            }), UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.top, UrlParser$ReactTemplate.s("about")), UrlParser$ReactTemplate.string(/* () */0)));
      var urlToRoute2 = UrlParser$ReactTemplate.oneOf(UrlParser$ReactTemplate.$neg$great$great(homeRoute, aboutRoute));
      var urlToRoute = function (url, _) {
        return Belt_Option.getExn(UrlParser$ReactTemplate.parseRouterUrl(urlToRoute2, url));
      };
      var transition = function (route) {
        if (typeof route === "number") {
          return Promise.resolve(React.createElement("div", undefined, "NF"));
        } else if (route.tag) {
          return Promise.resolve(ReasonReact.element(undefined, undefined, make$1(Curry._1(Service[/* fetchDataAbout */1], route[0]), /* array */[])));
        } else {
          var number = route[0];
          return timePromise(3000).then((function () {
                        return Promise.resolve(ReasonReact.element(undefined, undefined, make(number, /* array */[])));
                      }));
        }
      };
      return /* module */Block.localModule([
                "urlToRoute",
                "transition"
              ], [
                urlToRoute,
                transition
              ]);
    });
}

var initialState = /* record */Block.record([
    "error",
    "notification"
  ], [
    undefined,
    undefined
  ]);

function reducer(action, state) {
  if (action) {
    return /* tuple */[
            /* record */Block.record([
                "error",
                "notification"
              ], [
                action[0],
                state[/* notification */1]
              ]),
            /* [] */0
          ];
  } else {
    return /* tuple */[
            /* record */Block.record([
                "error",
                "notification"
              ], [
                undefined,
                state[/* notification */1]
              ]),
            /* [] */0
          ];
  }
}

var store = GlobalStateManagement$ReactTemplate.Manager[/* make */5](reducer, initialState);

function renderWithStore(render) {
  return Curry._1(render, store);
}

var App = /* module */Block.localModule([
    "getMessages",
    "initialState",
    "reducer",
    "store",
    "renderWithStore"
  ], [
    getMessages,
    initialState,
    reducer,
    store,
    renderWithStore
  ]);

function showErrorModal(error, refreshError) {
  return React.createElement("div", undefined, $$Array.of_list(List.map((function (prim) {
                        return prim;
                      }), error[/* messages */0])), React.createElement("div", {
                  onClick: (function () {
                      return Curry._1(refreshError, /* () */0);
                    })
                }));
}

function header() {
  return React.createElement("div", undefined, "IAM HEADER");
}

function AppRoot(MainContent) {
  var blankPage = React.createElement("div", {
        className: "loading"
      });
  var component = ReasonReact.statelessComponent("AppRoot");
  var make = function (store, _) {
    return /* record */Block.record([
              "debugName",
              "reactClassInternal",
              "handedOffState",
              "willReceiveProps",
              "didMount",
              "didUpdate",
              "willUnmount",
              "willUpdate",
              "shouldUpdate",
              "render",
              "initialState",
              "retainedProps",
              "reducer",
              "subscriptions",
              "jsElementWrapped"
            ], [
              component[/* debugName */0],
              component[/* reactClassInternal */1],
              component[/* handedOffState */2],
              component[/* willReceiveProps */3],
              component[/* didMount */4],
              component[/* didUpdate */5],
              component[/* willUnmount */6],
              component[/* willUpdate */7],
              component[/* shouldUpdate */8],
              (function () {
                  return ReasonReact.element(undefined, undefined, ReactHelper$ReactTemplate.Fragment[/* make */0](/* array */[
                                  header(/* () */0),
                                  ReasonReact.element(undefined, undefined, Curry._5(MainContent[/* make */0], /* array */[], blankPage, (function () {
                                              return GlobalStateManagement$ReactTemplate.Manager[/* dispatch */6](store, /* DetectedError */Block.simpleVariant("DetectedError", [/* record */Block.record(["messages"], [Block.simpleVariant("::", [
                                                                    "PagePrepareError",
                                                                    /* [] */0
                                                                  ])])]));
                                            }), (function () {
                                              console.log("start_transition");
                                              return /* () */0;
                                            }), (function () {
                                              console.log("finish_transition");
                                              return /* () */0;
                                            })))
                                ]));
                }),
              component[/* initialState */10],
              component[/* retainedProps */11],
              component[/* reducer */12],
              component[/* subscriptions */13],
              component[/* jsElementWrapped */14]
            ]);
  };
  return /* module */Block.localModule([
            "blankPage",
            "component",
            "make"
          ], [
            blankPage,
            component,
            make
          ]);
}

var MainContent = Routing$ReactTemplate.Application((function (Service) {
          var HomeExternalService = [Service[0]];
          var component = ReasonReact.statelessComponent("HomeContainer");
          var make = function (number, _) {
            return /* record */Block.record([
                      "debugName",
                      "reactClassInternal",
                      "handedOffState",
                      "willReceiveProps",
                      "didMount",
                      "didUpdate",
                      "willUnmount",
                      "willUpdate",
                      "shouldUpdate",
                      "render",
                      "initialState",
                      "retainedProps",
                      "reducer",
                      "subscriptions",
                      "jsElementWrapped"
                    ], [
                      component[/* debugName */0],
                      component[/* reactClassInternal */1],
                      component[/* handedOffState */2],
                      component[/* willReceiveProps */3],
                      component[/* didMount */4],
                      component[/* didUpdate */5],
                      component[/* willUnmount */6],
                      component[/* willUpdate */7],
                      component[/* shouldUpdate */8],
                      (function () {
                          var __x = GlobalStateManagement$ReactTemplate.Manager[/* getState */2](store)[/* notification */1];
                          var __x$1 = Belt_Option.map(__x, (function (param) {
                                  return Operator$ReactTemplate.$great$great(getMessages, List.hd, param);
                                }));
                          var notification = Belt_Option.getWithDefault(__x$1, "");
                          return React.createElement("div", undefined, React.createElement("div", undefined, String(number)), React.createElement("div", undefined, notification), Curry._1(HomeExternalService[/* fetchDataHome */0], "HOME"));
                        }),
                      component[/* initialState */10],
                      component[/* retainedProps */11],
                      component[/* reducer */12],
                      component[/* subscriptions */13],
                      component[/* jsElementWrapped */14]
                    ]);
          };
          var component$1 = ReasonReact.statelessComponent("AboutContainer");
          var make$1 = function (string, _) {
            return /* record */Block.record([
                      "debugName",
                      "reactClassInternal",
                      "handedOffState",
                      "willReceiveProps",
                      "didMount",
                      "didUpdate",
                      "willUnmount",
                      "willUpdate",
                      "shouldUpdate",
                      "render",
                      "initialState",
                      "retainedProps",
                      "reducer",
                      "subscriptions",
                      "jsElementWrapped"
                    ], [
                      component$1[/* debugName */0],
                      component$1[/* reactClassInternal */1],
                      component$1[/* handedOffState */2],
                      component$1[/* willReceiveProps */3],
                      component$1[/* didMount */4],
                      component$1[/* didUpdate */5],
                      component$1[/* willUnmount */6],
                      component$1[/* willUpdate */7],
                      component$1[/* shouldUpdate */8],
                      (function () {
                          return React.createElement("div", undefined, React.createElement("div", undefined, string));
                        }),
                      component$1[/* initialState */10],
                      component$1[/* retainedProps */11],
                      component$1[/* reducer */12],
                      component$1[/* subscriptions */13],
                      component$1[/* jsElementWrapped */14]
                    ]);
          };
          var homeRoute = UrlParser$ReactTemplate.toRoute((function (intValue) {
                  return /* Home */Block.variant("Home", 0, [intValue]);
                }), UrlParser$ReactTemplate.$pipe$unknown(UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.top, UrlParser$ReactTemplate.s("src")), UrlParser$ReactTemplate.s("index.html")), UrlParser$ReactTemplate.intParamWithDefault("name", 0)));
          var aboutRoute = UrlParser$ReactTemplate.toRoute((function (str) {
                  return /* About */Block.variant("About", 1, [str]);
                }), UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.$slash(UrlParser$ReactTemplate.top, UrlParser$ReactTemplate.s("about")), UrlParser$ReactTemplate.string(/* () */0)));
          var urlToRoute2 = UrlParser$ReactTemplate.oneOf(UrlParser$ReactTemplate.$neg$great$great(homeRoute, aboutRoute));
          var urlToRoute = function (url, _) {
            return Belt_Option.getExn(UrlParser$ReactTemplate.parseRouterUrl(urlToRoute2, url));
          };
          var transition = function (route) {
            if (typeof route === "number") {
              return Promise.resolve(React.createElement("div", undefined, "NF"));
            } else if (route.tag) {
              return Promise.resolve(ReasonReact.element(undefined, undefined, make$1(Curry._1(Service[/* fetchDataAbout */1], route[0]), /* array */[])));
            } else {
              var number = route[0];
              return timePromise(3000).then((function () {
                            return Promise.resolve(ReasonReact.element(undefined, undefined, make(number, /* array */[])));
                          }));
            }
          };
          return /* module */Block.localModule([
                    "urlToRoute",
                    "transition"
                  ], [
                    urlToRoute,
                    transition
                  ]);
        })(AllExternalSerciceImpl));

var blankPage = React.createElement("div", {
      className: "loading"
    });

var component = ReasonReact.statelessComponent("AppRoot");

function make(store, _) {
  return /* record */Block.record([
            "debugName",
            "reactClassInternal",
            "handedOffState",
            "willReceiveProps",
            "didMount",
            "didUpdate",
            "willUnmount",
            "willUpdate",
            "shouldUpdate",
            "render",
            "initialState",
            "retainedProps",
            "reducer",
            "subscriptions",
            "jsElementWrapped"
          ], [
            component[/* debugName */0],
            component[/* reactClassInternal */1],
            component[/* handedOffState */2],
            component[/* willReceiveProps */3],
            component[/* didMount */4],
            component[/* didUpdate */5],
            component[/* willUnmount */6],
            component[/* willUpdate */7],
            component[/* shouldUpdate */8],
            (function () {
                return ReasonReact.element(undefined, undefined, ReactHelper$ReactTemplate.Fragment[/* make */0](/* array */[
                                header(/* () */0),
                                ReasonReact.element(undefined, undefined, Curry._5(MainContent[/* make */0], /* array */[], blankPage, (function () {
                                            return GlobalStateManagement$ReactTemplate.Manager[/* dispatch */6](store, /* DetectedError */Block.simpleVariant("DetectedError", [/* record */Block.record(["messages"], [Block.simpleVariant("::", [
                                                                  "PagePrepareError",
                                                                  /* [] */0
                                                                ])])]));
                                          }), (function () {
                                            console.log("start_transition");
                                            return /* () */0;
                                          }), (function () {
                                            console.log("finish_transition");
                                            return /* () */0;
                                          })))
                              ]));
              }),
            component[/* initialState */10],
            component[/* retainedProps */11],
            component[/* reducer */12],
            component[/* subscriptions */13],
            component[/* jsElementWrapped */14]
          ]);
}

var AppRootImpl = /* module */Block.localModule([
    "blankPage",
    "component",
    "make"
  ], [
    blankPage,
    component,
    make
  ]);

function render() {
  return ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, make(store, /* array */[])), "index");
}

exports.Utils = Utils;
exports.$eq$eq$great = $eq$eq$great;
exports.HomeExternalServiceImpl = HomeExternalServiceImpl;
exports.AboutExternalServiceImpl = AboutExternalServiceImpl;
exports.AllExternalSerciceImpl = AllExternalSerciceImpl;
exports.StateManagementDef = StateManagementDef;
exports.MakeHomeContainer = MakeHomeContainer;
exports.MakeAboutContainer = MakeAboutContainer;
exports.MainContentRouting = MainContentRouting;
exports.App = App;
exports.showErrorModal = showErrorModal;
exports.header = header;
exports.AppRoot = AppRoot;
exports.AppRootImpl = AppRootImpl;
exports.render = render;
/* store Not a pure module */
