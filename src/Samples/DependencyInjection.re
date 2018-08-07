module type ServiceComponent = {let execute: string => string;};

module type Service = {let apply: string => string;};

module ServiceFunctor = (C: ServiceComponent) : Service => {
  let apply = arg => C.execute(arg) ++ "Functor";
};

module Application = (S: Service) => {
  let run = arg => S.apply(arg) ++ "Application";
};

type useServiceA('a) = {.. serviceA: int => int} as 'a;

type useServiceB('b) = {.. serviceB: int => int} as 'b;

type cC('a) =
  | C;

type cA = cC(int);

let depmodules: useServiceA(useServiceB({..})) = {
  pub serviceA = value => 0 + value;
  pub serviceB = value => 100 + value
};
