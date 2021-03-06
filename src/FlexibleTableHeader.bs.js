// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");

function getWidthSize(size) {
  if (typeof size === "number") {
    switch (size) {
      case 0 : 
          return 7.0;
      case 1 : 
          return 9.5;
      case 2 : 
          return 12.0;
      
    }
  } else {
    return size[0];
  }
}

function headerItemToJs(param) {
  return {
          column: param[/* column */0],
          size: param[/* size */1],
          isSizeFixed: param[/* isSizeFixed */2]
        };
}

function headerItemFromJs(param) {
  return /* record */Block.record([
            "column",
            "size",
            "isSizeFixed"
          ], [
            param.column,
            param.size,
            param.isSizeFixed
          ]);
}

function valueToString(func, value) {
  return JSON.stringify(Curry._1(func, value));
}

function stringFromValue(func, anyString) {
  return Curry._1(func, JSON.parse(anyString));
}

function getWidthSizeByTableWidthSize(tableWidthSize, header) {
  var getHeaderItemWidthSize = function (headerItem) {
    return getWidthSize(headerItem[/* size */1]);
  };
  var headerSizeList = List.map(getHeaderItemWidthSize, header);
  var totalHeaderSize = List.fold_left((function (prim, prim$1) {
          return prim + prim$1;
        }), 0.0, headerSizeList);
  if (tableWidthSize > totalHeaderSize) {
    var flexibleSizeHeaderCount = List.length(List.filter((function (header) {
                  return !header[/* isSizeFixed */2];
                }))(header));
    var totalSizeFiexedWidth = List.fold_left((function (prim, prim$1) {
            return prim + prim$1;
          }), 0.0, List.map(getHeaderItemWidthSize, List.filter((function (header) {
                      return header[/* isSizeFixed */2];
                    }))(header)));
    var headerSize = (tableWidthSize - totalSizeFiexedWidth) / flexibleSizeHeaderCount;
    return List.map((function (headerItem) {
                  return /* record */Block.record([
                            "column",
                            "size",
                            "isSizeFixed"
                          ], [
                            headerItem[/* column */0],
                            Block.simpleVariant("Free", [headerSize]),
                            headerItem[/* isSizeFixed */2]
                          ]);
                }), header);
  } else if (tableWidthSize === 0.0) {
    return List.map((function (headerItem) {
                  return /* record */Block.record([
                            "column",
                            "size",
                            "isSizeFixed"
                          ], [
                            headerItem[/* column */0],
                            Block.simpleVariant("Free", [0.0]),
                            headerItem[/* isSizeFixed */2]
                          ]);
                }), header);
  } else {
    return header;
  }
}

exports.getWidthSize = getWidthSize;
exports.headerItemToJs = headerItemToJs;
exports.headerItemFromJs = headerItemFromJs;
exports.valueToString = valueToString;
exports.stringFromValue = stringFromValue;
exports.getWidthSizeByTableWidthSize = getWidthSizeByTableWidthSize;
/* No side effect */
