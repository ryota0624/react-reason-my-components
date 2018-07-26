// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Page$ReactTemplate = require("./Page.bs.js");
var Helpers$ReactTemplate = require("./Helpers.bs.js");
var Tooltip$ReactTemplate = require("./Tooltip.bs.js");
var ModalSample$ReactTemplate = require("./ModalSample.bs.js");
var PromiseWrapper$ReactTemplate = require("./PromiseWrapper.bs.js");
var IncrementalSearch$ReactTemplate = require("./IncrementalSearch.bs.js");
var TodoFlexibleTable$ReactTemplate = require("./Samples/TodoFlexibleTable.bs.js");

var IntPromiseWrapperDef = /* module */Block.localModule([], []);

var IntPromiseWrapper = PromiseWrapper$ReactTemplate.PromiseWrapper(IntPromiseWrapperDef);

function whenSuccess(v) {
  return React.createElement("div", undefined, String(v));
}

function whenError() {
  return React.createElement("div", undefined, React.createElement("p", undefined, "ERROR!"));
}

var whenPending = React.createElement("div", undefined, React.createElement("p", undefined, "NowLoading..."));

function r() {
  return /* () */0;
}

function timePromise(count) {
  return new Promise((function (resolve, _) {
                setTimeout((function () {
                        return resolve(count);
                      }), count);
                return /* () */0;
              }));
}

var allEntities = /* :: */Block.simpleVariant("::", [
    "Apple",
    /* :: */Block.simpleVariant("::", [
        "Banana",
        /* :: */Block.simpleVariant("::", [
            "All",
            /* :: */Block.simpleVariant("::", [
                "Berry",
                /* [] */0
              ])
          ])
      ])
  ]);

function findEntities(text) {
  return new Promise((function (resolve, _) {
                return resolve(List.filter((function (__x) {
                                    return Helpers$ReactTemplate.$$String[/* contain */0](__x, text);
                                  }))(allEntities));
              }));
}

var TextIncrementalSearchDef = /* module */Block.localModule([
    "allEntities",
    "findEntities"
  ], [
    allEntities,
    findEntities
  ]);

var TextIncrementalSearch = IncrementalSearch$ReactTemplate.IncrementalSearch([findEntities]);

function SamplePage(Resolver) {
  var initialize = function (resource) {
    return /* record */Block.record([
              "value",
              "name"
            ], [
              resource[0],
              resource[1]
            ]);
  };
  var render = function (t) {
    var name = t[/* name */1];
    var valueStr = String(t[/* value */0]);
    return name + valueStr;
  };
  var loadResource = function (arg) {
    return Curry._1(Resolver[/* loadResource */0], 1009).then((function (value) {
                  return Promise.resolve(/* tuple */[
                              value,
                              String(value) + arg
                            ]);
                }));
  };
  return /* module */Block.localModule([
            "componentName",
            "initialize",
            "render",
            "loadResource"
          ], [
            "SampleIntPage",
            initialize,
            render,
            loadResource
          ]);
}

var loadResource = timePromise;

var SamplePageResolverImpl = /* module */Block.localModule(["loadResource"], [loadResource]);

var ResourcePromiseWrapperDef = /* module */Block.localModule([], []);

function initialize(resource) {
  return /* record */Block.record([
            "value",
            "name"
          ], [
            resource[0],
            resource[1]
          ]);
}

function render(t) {
  var name = t[/* name */1];
  var valueStr = String(t[/* value */0]);
  return name + valueStr;
}

function loadResource$1(arg) {
  return timePromise(1009).then((function (value) {
                return Promise.resolve(/* tuple */[
                            value,
                            String(value) + arg
                          ]);
              }));
}

var SamplePageImpl = Page$ReactTemplate.Make(/* module */Block.localModule([
          "componentName",
          "initialize",
          "render",
          "loadResource"
        ], [
          "SampleIntPage",
          initialize,
          render,
          loadResource$1
        ]))(ResourcePromiseWrapperDef);

ReactDOMRe.renderToElementWithId(React.createElement("div", undefined, ReasonReact.element(undefined, undefined, Tooltip$ReactTemplate.make(/* Down */2, /* Large */2, "IAM TOOLTIP", React.createElement("button", {
                      className: "target"
                    }, "HELLO"), /* array */[])), ReasonReact.element(undefined, undefined, TodoFlexibleTable$ReactTemplate.TodoTableSample[/* make */3](/* array */[])), ReasonReact.element(undefined, undefined, Curry._5(IntPromiseWrapper[/* make */1], timePromise(1000), whenSuccess, whenError, whenPending, /* array */[])), ReasonReact.element(undefined, undefined, ModalSample$ReactTemplate.make(/* array */[])), ReasonReact.element(undefined, undefined, Curry._4(TextIncrementalSearch[/* make */2], undefined, undefined, (function (results) {
                    return React.createElement("ul", undefined, $$Array.of_list(List.map((function (text) {
                                          return React.createElement("li", {
                                                      key: text
                                                    }, text);
                                        }), results)));
                  }), /* array */[])), ReasonReact.element(undefined, undefined, Curry._2(SamplePageImpl[/* make */5], "HOGE", /* array */[]))), "index");

function add(x, y, z) {
  return (x + y | 0) + z | 0;
}

var addFiveOops = add(5, 4, 4);

function add2(x, y, z) {
  return (x + y | 0) + z | 0;
}

var addFiveOops2 = add2(5, 4, 4);

function add3(x, y, z) {
  return (x + y | 0) + z | 0;
}

var PromiseWrapper = PromiseWrapper$ReactTemplate.PromiseWrapper;

var addFiveOops3 = 13;

exports.PromiseWrapper = PromiseWrapper;
exports.IntPromiseWrapperDef = IntPromiseWrapperDef;
exports.IntPromiseWrapper = IntPromiseWrapper;
exports.whenSuccess = whenSuccess;
exports.whenError = whenError;
exports.whenPending = whenPending;
exports.r = r;
exports.timePromise = timePromise;
exports.TextIncrementalSearchDef = TextIncrementalSearchDef;
exports.TextIncrementalSearch = TextIncrementalSearch;
exports.SamplePage = SamplePage;
exports.SamplePageResolverImpl = SamplePageResolverImpl;
exports.ResourcePromiseWrapperDef = ResourcePromiseWrapperDef;
exports.SamplePageImpl = SamplePageImpl;
exports.add = add;
exports.addFiveOops = addFiveOops;
exports.add2 = add2;
exports.addFiveOops2 = addFiveOops2;
exports.add3 = add3;
exports.addFiveOops3 = addFiveOops3;
/* IntPromiseWrapper Not a pure module */
