open Belt;
open ReasonReact.Router;

type state('value) = {
  visited: list(string),
  unvisited: list(string),
  params: Map.String.t(string),
  value: 'value,
};

type parser('a, 'b) =
  | Parser(state('a) => list(state('b)));

let custom = (_: string, stringToValue: string => Result.t('a, string)) =>
  Parser(
    ({visited, unvisited, params, value}) =>
      switch (unvisited) {
      | [] => []
      | [next, ...rest] =>
        switch (stringToValue(next)) {
        | Result.Ok(nextValue) => [
            {
              visited: List.concat([next], visited),
              unvisited: rest,
              params,
              value: value(nextValue),
            },
          ]
        | Result.Error(_) => []
        }
      },
  );

let s = str =>
  Parser(
    ({visited, unvisited, params, value}) =>
      switch (unvisited) {
      | [] => []
      | [next, ...rest] =>
        if (next == str) {
          [
            {
              visited: List.concat([next], visited),
              unvisited: rest,
              params,
              value,
            },
          ];
        } else {
          [];
        }
      },
  );

/** https://ocamlverse.github.io/content/weak_type_variables.html
 * unitをとって関数が実行されると、実行の文脈から型が決まってコンパイルエラーにならない？
 */
let string = () : parser(string => 'a, 'a) =>
  custom("STRING", (v: string) => Result.Ok(v));

let int = () : parser(int => 'a, 'a) =>
  custom("INT", v =>
    try (Ok(int_of_string(v))) {
    | Failure(msg) => Result.Error(msg)
    }
  );

let (</\/>) = (Parser(parseBefore), Parser(parseAfter)) =>
  Parser(
    state => parseBefore(state) |> List.map(_, parseAfter) |> List.flatten,
  );

let mapHelp = (func, {visited, unvisited, params, value}) => {
  visited,
  unvisited,
  params,
  value: func(value),
};

let map = (subValue, Parser(parse)) =>
  Parser(
    ({visited, unvisited, params, value}) => {
      let parsed = parse({visited, unvisited, params, value: subValue});
      List.map(parsed, mapHelp(value));
    },
  );

let oneOf = parsers =>
  Parser(
    state =>
      parsers
      |> List.map(_, (Parser(parse)) => parse(state))
      |> List.flatten,
  );

let top = Parser(state => [state]);

let rec parseHelp = states =>
  switch (states) {
  | [] => None
  | [state, ...rest] =>
    switch (state.unvisited) {
    | [] => Some(state.value)
    | [""] => Some(state.value)
    | _ => parseHelp(rest)
    }
  };

let splitUrl = url =>
  switch (Js.String.split("/", url) |> List.fromArray) {
  | ["", ...segments] => segments
  | segments => segments
  };

let parse = (Parser(parse), parsedUrl, params) =>
  parseHelp(
    parse({visited: [], unvisited: parsedUrl, params, value: v => v}),
  );

let parseRouterUrl = (parser, url: ReasonReact.Router.url) =>
  parse(parser, url.path, ReactHelper.Router.routeToqueryParamMap(url));

module Sample = {
  type route =
    | Home(string, string)
    | AB(string);
  let home = (v1, v2) => Home(v1, v2);
  let ab = v => AB(v);
  let start = () => {
    Js.Console.log("Start");

    let successRoute = top </\/> string() </\/> string();
    let failRoute = top </\/> string() </\/> s("fail");
    let parser = oneOf([map(home, successRoute), map(ab, failRoute)]);

    Js.Console.log(ReasonReact.Router.dangerouslyGetInitialUrl());

    let parsed =
      parseRouterUrl(parser, ReasonReact.Router.dangerouslyGetInitialUrl());

    Js.Console.log(parsed);
  };
};
