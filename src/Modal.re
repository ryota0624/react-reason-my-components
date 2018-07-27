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
    ~left="0",
    ~right="0",
    ~position="fixed",
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
    ~position="fixed",
    (),
  );

let modalBgStyle =
  ReactDOMRe.Style.make(
    ~zIndex="1049",
    ~backgroundColor="rgba(41, 38, 38, 0.5)",
    ~top="0",
    ~left="0",
    ~position="fixed",
    ~width="100%",
    ~height="100%",
    (),
  );

let modalBgHiddenStyle = ReactDOMRe.Style.make();

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
  render: _ => {
    let modalClassName =
      "modal modal-dialog fade modal-dialog-centered "
      ++ modalSizeToAttr(size);
    <ReactHelper.Fragment>
      <div
        className=modalClassName
        style=(hidden ? modalHiddenStyle : modalOpenStyle)
        onClick=ReactEventRe.Synthetic.stopPropagation>
        <div className="modal-content">
          (header |> ReactHelper.option)
          (body |> ReactHelper.option)
          (footer |> ReactHelper.option)
        </div>
      </div>
      <span
        style=(hidden ? modalBgHiddenStyle : modalBgStyle)
        onClick=(_ => onClickContentOutside |> ReactHelper.optionalHandler)
      />
    </ReactHelper.Fragment>;
  },
};
