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
    <ModalSample />
  </div>,
  "index",
);
