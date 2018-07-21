open DependencyInjection;
open DiComponent;

module RealService = ServiceFunctor(ServiceComponentImpl);
module MockService = ServiceFunctor(ServiceComponentMock);
module MockFileUnitService = ServiceFunctor(DiComponent);

module RealApplication = Application(MockFileUnitService);

let () = {
  let result = RealApplication.run("run");
  Js.Console.log(result);
};
