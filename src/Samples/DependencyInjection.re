module type ServiceComponent = {
  let execute: string => string;
};

module type Service = {
  let apply: string => string;
};

module ServiceFunctor = (C: ServiceComponent): Service => {
  let apply = (arg) => C.execute(arg) ++ "Functor";
}

module Application = (S: Service) => {
  let run = (arg) => S.apply(arg) ++ "Application"
}