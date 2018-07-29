
module type Leaf = {
  type t;
  let identity: t => string
};

module Tree = (L: Leaf) => {
  type tree = Leaf(L.t) | Node(list(tree));

  let lead = (t: L.t) => Leaf(t);
  let node = (tree: tree) => Node([tree]);

  let rec updateLeaf = (t: L.t, tree: tree) => {
    switch (tree) {
    | Leaf(data) => 
      if ((data |> L.identity) == (t |> L.identity)) {
        Leaf(t);
      } else Leaf(data);
    | Node(nodes) => 
    /**
     * TODO すべてのnodesを更新して入れ替えるように実装
     */
     /* updateLeaf(t, tree); */
    }
  };
}