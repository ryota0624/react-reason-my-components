module type Leaf = {
  type t;
  let identity: t => string;
  let showLeaf: t => ReasonReact.reactElement;
};

module MyString = {
  let join = (strings: list(string)) : string =>
    List.fold_left((a, b) => a ++ b, "", strings);
};

module Tree = (L: Leaf) => {
  type tree =
    | Leaf(L.t)
    | Node(list(tree));

  let leaf = (t: L.t) => Leaf(t);
  let node = (tree: list(tree)) => Node(tree);

  let rec nodeIdentity = (tree: tree) : string =>
    switch (tree) {
    | Leaf(data) => "leaf-" ++ L.identity(data)
    | Node(datas) =>
      "node-" ++ (datas |> List.map(nodeIdentity) |> MyString.join)
    };

  let rec updateLeaf = (t: L.t, tree: tree) =>
    switch (tree) {
    | Leaf(data) =>
      if (data |> L.identity == (t |> L.identity)) {
        Leaf(t);
      } else {
        Leaf(data);
      }
    | Node(nodes) =>
      nodes |> List.map(updateLeaf(t)) |> (nodes => Node(nodes))
    };

  let rec showTree = (tree: tree) : ReasonReact.reactElement =>
    switch (tree) {
    | Leaf(data) =>
      <span key=(nodeIdentity(Leaf(data)))> (L.showLeaf(data)) </span>
    | Node(nodes) =>
      nodes
      |> List.map(showTree)
      |> (
        reactElmList =>
          <div key=(nodeIdentity(Node(nodes)))>
            (reactElmList |> Array.of_list |> ReasonReact.array)
          </div>
      )
    };
};
