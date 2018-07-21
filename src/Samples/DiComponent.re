open DependencyInjection;

module ServiceComponentImpl: ServiceComponent = {
  let execute = argString => argString ++ "Impl";
};

module ServiceComponentMock: ServiceComponent = {
  let execute = argString => argString ++ "Mock";
};

let execute = argString => argString ++ "MockFile";
