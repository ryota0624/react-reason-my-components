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
    ~zIndex="1050",
    ~top="0",
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
    ~zIndex="1050",
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
    <ReactHelper.Fragment>
      <div
        className=("modal modal-dialog fade modal-dialog-centered " ++ modalSizeToAttr(size))
        style=(hidden ? modalHiddenStyle : modalOpenStyle)
        onClick=(ReactEventRe.Synthetic.stopPropagation)>
        <div className="modal-content">
          (header |> ReactHelper.option)
          (body |> ReactHelper.option)
          (footer |> ReactHelper.option)
        </div>
      </div>
    <div className=(hidden ? "h-bd" : "o-bd")
      onClick=(_ => onClickContentOutside |> ReactHelper.optionalHandler)
    /> 
    </ReactHelper.Fragment>
    ,
};
