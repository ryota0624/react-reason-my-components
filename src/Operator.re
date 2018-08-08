let andThen = (a, b, v) => b(a(v));
let (>>) = andThen;
let (<|) = (a, b) => a(b);

let always = (b) => () => b;

let identity = (a) => a;