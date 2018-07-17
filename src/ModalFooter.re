let component = ReasonReact.statelessComponent("ModalFooterComponent");

let make = _children => {
  ...component,
  render: _ => <div className="modal-footer"> _children </div>,
};
