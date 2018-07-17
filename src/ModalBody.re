let component = ReasonReact.statelessComponent("ModalBodyComponent");

let make = (_children: ReasonReact.reactElement) => {
  ...component,
  render: _ => <div className="modal-body"> _children </div>,
};
