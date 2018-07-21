include PromiseWrapper;
module IntPromiseWrapperDef = {
  type v = int;
};

module IntPromiseWrapper = PromiseWrapper(IntPromiseWrapperDef);

let whenSuccess= (v) => <div> (ReasonReact.string(string_of_int(v))) </div> ;

let whenError = (_) => <div> <p> (ReasonReact.string("ERROR!")) </p> </div>;

let whenPending =  <div> <p> (ReasonReact.string("NowLoading...")) </p> </div>;

let r = () => ();

let timePromise = count => Js.Promise.make((~resolve, ~reject as _) => {
  /* https://bucklescript.github.io/bucklescript/Manual.html#__code_bs_code_for_explicit_uncurried_callback */
  /* (. 引数) で引数をuncurryすることを明示してる */
  /* promiseのここだとよくわからないけど
     Array.mapとか
     Array.map((n) => 1 + n, [4,4])みたいにbsで書くと
     Array.map((n) => 1 + n)([4,4])ってjsになっちゃうからかな？
  */
  let _ = Js.Global.setTimeout(() => resolve(. count), count);
});

ReactDOMRe.renderToElementWithId(
  <div>
    <Tooltip
      position=Tooltip.Down
      size=Tooltip.Large
      text="IAM TOOLTIP"
      parent={
        <button className="target"> (ReasonReact.string("HELLO")) </button>
      }
    />
    <TodoFlexibleTable.TodoTableSample />
    <IntPromiseWrapper 
      promise=(timePromise(1000))
      whenError=whenError
      whenPending=whenPending
      whenSuccess=whenSuccess
    />
    <ModalSample />
  </div>,
  "index",
);

let add = (. x, y, z) => x + y + z;
let addFiveOops = [@bs] add(5,4,4);

let add2 = (. x, y, z) => x + y + z;
let addFiveOops2 = add2(. 5,4,4);

let add3 = (x, y, z) => x + y + z;
let addFiveOops3 = add3(5,4,4);