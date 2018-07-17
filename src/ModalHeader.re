let component = ReasonReact.statelessComponent("ModalHeaderComponent");

let make = (~title, _children) => {
  ...component,
  render: _ =>
    <div className="modal-header">
      (
        ReasonReact.cloneElement(
          title,
          ~props={"className": "modal-title"},
          [||],
        )
      )
      _children
    </div>,
};
