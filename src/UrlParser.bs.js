// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Js_exn = require("bs-platform/lib/js/js_exn.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");
var Belt_MapString = require("bs-platform/lib/js/belt_MapString.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");
var ReactHelper$ReactTemplate = require("./ReactHelper.bs.js");

function custom(_, stringToValue) {
  return /* Parser */Block.simpleVariant("Parser", [(function (param) {
                var unvisited = param[/* unvisited */1];
                if (unvisited) {
                  var next = unvisited[0];
                  var match = Curry._1(stringToValue, next);
                  if (match.tag) {
                    return /* [] */0;
                  } else {
                    return /* :: */Block.simpleVariant("::", [
                              /* record */Block.record([
                                  "visited",
                                  "unvisited",
                                  "params",
                                  "value"
                                ], [
                                  Belt_List.concat(/* :: */Block.simpleVariant("::", [
                                          next,
                                          /* [] */0
                                        ]), param[/* visited */0]),
                                  unvisited[1],
                                  param[/* params */2],
                                  Curry._1(param[/* value */3], match[0])
                                ]),
                              /* [] */0
                            ]);
                  }
                } else {
                  return /* [] */0;
                }
              })]);
}

function s(str) {
  return /* Parser */Block.simpleVariant("Parser", [(function (param) {
                var unvisited = param[/* unvisited */1];
                if (unvisited) {
                  var next = unvisited[0];
                  if (next === str) {
                    return /* :: */Block.simpleVariant("::", [
                              /* record */Block.record([
                                  "visited",
                                  "unvisited",
                                  "params",
                                  "value"
                                ], [
                                  Belt_List.concat(/* :: */Block.simpleVariant("::", [
                                          next,
                                          /* [] */0
                                        ]), param[/* visited */0]),
                                  unvisited[1],
                                  param[/* params */2],
                                  param[/* value */3]
                                ]),
                              /* [] */0
                            ]);
                  } else {
                    return /* [] */0;
                  }
                } else {
                  return /* [] */0;
                }
              })]);
}

function string() {
  return custom("STRING", (function (v) {
                return /* Ok */Block.variant("Ok", 0, [v]);
              }));
}

function $$int() {
  return custom("INT", (function (v) {
                try {
                  return /* Ok */Block.variant("Ok", 0, [Caml_format.caml_int_of_string(v)]);
                }
                catch (raw_exn){
                  var exn = Js_exn.internalToOCamlException(raw_exn);
                  if (exn[0] === Caml_builtin_exceptions.failure) {
                    return /* Error */Block.variant("Error", 1, [exn[1]]);
                  } else {
                    throw exn;
                  }
                }
              }));
}

function $slash(param, param$1) {
  var parseAfter = param$1[0];
  var parseBefore = param[0];
  return /* Parser */Block.simpleVariant("Parser", [(function (state) {
                var __x = Curry._1(parseBefore, state);
                return Belt_List.flatten(Belt_List.map(__x, parseAfter));
              })]);
}

function mapHelp(func, param) {
  return /* record */Block.record([
            "visited",
            "unvisited",
            "params",
            "value"
          ], [
            param[/* visited */0],
            param[/* unvisited */1],
            param[/* params */2],
            Curry._1(func, param[/* value */3])
          ]);
}

function map(subValue, param) {
  var parse = param[0];
  return /* Parser */Block.simpleVariant("Parser", [(function (param) {
                var value = param[/* value */3];
                var parsed = Curry._1(parse, /* record */Block.record([
                        "visited",
                        "unvisited",
                        "params",
                        "value"
                      ], [
                        param[/* visited */0],
                        param[/* unvisited */1],
                        param[/* params */2],
                        subValue
                      ]));
                return Belt_List.map(parsed, (function (param) {
                              return mapHelp(value, param);
                            }));
              })]);
}

function $eq$great$great(p, s) {
  return /* :: */Block.simpleVariant("::", [
            map(s, p),
            /* [] */0
          ]);
}

function oneOf(parsers) {
  return /* Parser */Block.simpleVariant("Parser", [(function (state) {
                return Belt_List.flatten(Belt_List.map(parsers, (function (param) {
                                  return Curry._1(param[0], state);
                                })));
              })]);
}

var top = /* Parser */Block.simpleVariant("Parser", [(function (state) {
        return /* :: */Block.simpleVariant("::", [
                  state,
                  /* [] */0
                ]);
      })]);

function parseHelp(_states) {
  while(true) {
    var states = _states;
    if (states) {
      var rest = states[1];
      var state = states[0];
      var match = state[/* unvisited */1];
      if (match) {
        if (match[0] === "") {
          if (match[1]) {
            _states = rest;
            continue ;
          } else {
            return Js_primitive.some(state[/* value */3]);
          }
        } else {
          _states = rest;
          continue ;
        }
      } else {
        return Js_primitive.some(state[/* value */3]);
      }
    } else {
      return undefined;
    }
  };
}

function splitUrl(url) {
  var segments = Belt_List.fromArray(url.split("/"));
  if (segments && segments[0] === "") {
    return segments[1];
  } else {
    return segments;
  }
}

function parse(param, parsedUrl, params) {
  return parseHelp(Curry._1(param[0], /* record */Block.record([
                    "visited",
                    "unvisited",
                    "params",
                    "value"
                  ], [
                    0,
                    parsedUrl,
                    params,
                    (function (v) {
                        return v;
                      })
                  ])));
}

function parseRouterUrl(parser, url) {
  return parse(parser, url[/* path */0], ReactHelper$ReactTemplate.Router[/* routeToqueryParamMap */3](url));
}

var $neg$great$great = Belt_List.concat;

function $pipe$unknown(param, param$1) {
  var queryParser = param$1[0];
  var parser = param[0];
  return /* Parser */Block.simpleVariant("Parser", [(function (state) {
                var __x = Curry._1(parser, state);
                return Belt_List.flatten(Belt_List.map(__x, queryParser));
              })]);
}

function customParam(key, func) {
  return /* QueryParser */Block.simpleVariant("QueryParser", [(function (param) {
                var params = param[/* params */2];
                return /* :: */Block.simpleVariant("::", [
                          /* record */Block.record([
                              "visited",
                              "unvisited",
                              "params",
                              "value"
                            ], [
                              param[/* visited */0],
                              param[/* unvisited */1],
                              params,
                              Curry._1(param[/* value */3], Curry._1(func, Belt_MapString.get(params, key)))
                            ]),
                          /* [] */0
                        ]);
              })]);
}

function stringParam(name) {
  return customParam(name, (function (v) {
                return v;
              }));
}

function intParam(name) {
  return customParam(name, (function (stringValueOpt) {
                return Belt_Option.flatMap(stringValueOpt, (function (stringValue) {
                              try {
                                return Caml_format.caml_int_of_string(stringValue);
                              }
                              catch (raw_exn){
                                var exn = Js_exn.internalToOCamlException(raw_exn);
                                if (exn[0] === Caml_builtin_exceptions.failure) {
                                  return undefined;
                                } else {
                                  throw exn;
                                }
                              }
                            }));
              }));
}

function toRoute(s, p) {
  return /* :: */Block.simpleVariant("::", [
            map(s, p),
            /* [] */0
          ]);
}

function andThen(a, b, v) {
  return Curry._1(b, Curry._1(a, v));
}

function home(v1, v2) {
  return /* Home */Block.variant("Home", 0, [
            v1,
            v2
          ]);
}

function ab(v, v2) {
  return /* AB */Block.variant("AB", 1, [
            v,
            v2
          ]);
}

function start() {
  console.log("Start");
  var homeRoute2 = toRoute(home, $slash($slash(top, custom("STRING", (function (v) {
                      return /* Ok */Block.variant("Ok", 0, [v]);
                    }))), custom("STRING", (function (v) {
                  return /* Ok */Block.variant("Ok", 0, [v]);
                }))));
  var homeRoute = $eq$great$great($slash($slash(top, custom("STRING", (function (v) {
                      return /* Ok */Block.variant("Ok", 0, [v]);
                    }))), custom("STRING", (function (v) {
                  return /* Ok */Block.variant("Ok", 0, [v]);
                }))), home);
  var abRoute = $eq$great$great($pipe$unknown($slash($slash($slash(top, custom("STRING", (function (v) {
                              return /* Ok */Block.variant("Ok", 0, [v]);
                            }))), s("fail")), s("hoge")), customParam("name", (function (v) {
                  return v;
                }))), ab);
  var route1 = Belt_List.concat(abRoute, homeRoute);
  var parser = oneOf(Belt_List.concat(route1, homeRoute2));
  var parsed = parseRouterUrl(parser, ReasonReact.Router[/* dangerouslyGetInitialUrl */3](/* () */0));
  ReasonReact.Router[/* watchUrl */1]((function (param) {
          var __x = parseRouterUrl(parser, param);
          console.log(Belt_Option.getWithDefault(__x, /* NotFound */0));
          return /* () */0;
        }));
  console.log(parsed);
  return /* () */0;
}

var Sample = /* module */Block.localModule([
    "andThen",
    ">>",
    "home",
    "ab",
    "start"
  ], [
    andThen,
    andThen,
    home,
    ab,
    start
  ]);

exports.custom = custom;
exports.s = s;
exports.string = string;
exports.$$int = $$int;
exports.$slash = $slash;
exports.mapHelp = mapHelp;
exports.map = map;
exports.$eq$great$great = $eq$great$great;
exports.oneOf = oneOf;
exports.top = top;
exports.parseHelp = parseHelp;
exports.splitUrl = splitUrl;
exports.parse = parse;
exports.parseRouterUrl = parseRouterUrl;
exports.$neg$great$great = $neg$great$great;
exports.$pipe$unknown = $pipe$unknown;
exports.customParam = customParam;
exports.stringParam = stringParam;
exports.intParam = intParam;
exports.toRoute = toRoute;
exports.Sample = Sample;
/* ReasonReact Not a pure module */
