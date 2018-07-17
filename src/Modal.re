let component = ReasonReact.statelessComponent("ModalComponent");

type modalSize =
  | Large
  | Small
  | Medium;

let modalSizeToAttr = size =>
  switch (size) {
  | Large => "modal-lg"
  | Small => "modal-sm"
  | Medium => ""
  };

let modalOpenStyle =
  ReactDOMRe.Style.make(
    ~display="block",
    ~visibility="visible",
    ~transition="all 0.5s",
    ~opacity="1",
    (),
  );

let modalHiddenStyle =
  ReactDOMRe.Style.make(
    ~display="block",
    ~visibility="hidden",
    ~transition="all 0.5s",
    ~top="-100vh",
    ~bottom="auto",
    ~opacity="1",
    ~pointerEvents="none",
    ~zIndex="-1",
    (),
  );

let make =
    (
      ~hidden,
      ~size,
      ~onClickContentOutside=?,
      ~header=?,
      ~footer=?,
      ~body=?,
      _children,
    ) => {
  ...component,
  render: _ =>
    <div
      style=(hidden ? modalHiddenStyle : modalOpenStyle)
      className=("modal" ++ (hidden ? " hidden" : " open"))
      onClick=(_ => onClickContentOutside |> ReactHelper.optionalHandler)>
      <div
        className=("modal-dialog " ++ modalSizeToAttr(size))
        onClick=(event => ReactEventRe.Synthetic.stopPropagation(event))>
        <div className="modal-content">
          (header |> ReactHelper.option)
          (body |> ReactHelper.option)
          (footer |> ReactHelper.option)
        </div>
      </div>
    </div>,
};
