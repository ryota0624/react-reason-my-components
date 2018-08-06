open Belt;
open ReasonReact.Router;

type state('value) = {
  visited: list(string),
  unvisited: list(string),
  params: Map.String.t(string),
  value: 'value
};

type parser('a, 'b) =
  Parser(state('a) => list(state('b)));

let custom = (_: string, stringToValue) =>
  Parser(({visited, unvisited, params, value}) => {
    switch (unvisited) {
    | [] => []
    | [next, ...rest] => 
      switch (stringToValue(next)) {
      | Result.Ok(nextValue) => [
          {
            visited: List.concat([next], visited),
            unvisited: rest,
            params: params,
            value: (value(nextValue))
          }
        ]
      | Result.Error(_) => [] 
      };
    };
  });
  
  
let (<//>) = (Parser(parseBefore), Parser(parseAfter)) => 
  Parser(
    (state) => parseBefore(state)
      |> List.map(_, parseAfter)
      |> List.flatten
  );

let mapHelp = (func, {visited, unvisited, params, value}) => {
  {
    visited,
    unvisited, 
    params,
    value: func(value)
  }
};

let map = (subValue, Parser(parse)) => {
  Parser(({visited, unvisited, params, value}) => {
      let parsed = parse({
        visited,
        unvisited,
        params,
        value: subValue
      });
      List.map(parsed, mapHelp(value))
    })
};

let oneOf = (parsers) => {
  Parser(state => {
    parsers
      |> List.map(_, (Parser(parse)) => parse(state))
      |> List.flatten
  });
};

let top = Parser(state => [state]);


let rec parseHelp = (states) => switch (states) {
  | [] => None
  | [state, ...rest] => switch (state.unvisited) {
    | [] => Some(state.value)
    | [""] => Some(state.value)
    | _ => parseHelp(rest) 
    };
  };
  
  let splitUrl = url => switch (Js.String.split("/", url) |> List.fromArray) {
  | ["", ...segments] => segments
  | segments => segments
  };

let parse = (Parser(parse), url, params) => {
  parseHelp(parse({
    visited: [], 
    unvisited: splitUrl(url),
    params: params,
    value: (v => v)
  }))
};

