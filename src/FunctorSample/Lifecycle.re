module type MVU = {
  type model;
  type msg;
  type error;
  type seed;

  let update: (msg, model) => (model, list(Js.Promise.t(msg)));
  let init: (seed) => model;
};

module MakePage = (Mvu: MVU) => {
  type page = {
    model: Mvu.model
  };

  let update = (msg: Mvu.msg, page: page): (page, list(Js.Promise.t(Mvu.msg))) => {
    Mvu.update(msg, page.model) |> ((tup) => ({model: tup |> fst}, tup |> snd))
  };

  let init = (seed: Mvu.seed): page => { model: Mvu.init(seed) };
};

type todoId = Id(string)

type todo = {
  id: todoId,
  title: string
};

module TodoMvu = {
  type model = list(todo);
  type msg = AddTodo(todo) | ReceiveTodos(list(todo)) | DeteteTodo(todoId);
  type error = NoError;
  type seed = todo

  let update = (msg, model) => {
    switch (msg) {
    | AddTodo(todo) => (List.append([todo], model), [])
    | ReceiveTodos(todos) => (todos, [])
    | DeteteTodo(id) => (List.filter((todo) => todo.id === id, model), [])
    }
  };

  let init = (seed: todo): model => [seed];
}

module TodoPage = MakePage(TodoMvu);

let todoPage = TodoPage.init({id: Id(""), title: "nama"});
let a = todoPage.model
let headTodo = a |> List.hd
let headTitleTodo = headTodo.title;

let (updatedTodoPage, promises) = TodoPage.update(TodoMvu.DeteteTodo(Id("")), todoPage);
let updatePromise = promises
  |> Array.of_list
  |> Js.Promise.all