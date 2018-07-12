

type action = 
  | Open
  | Close;

type state = {isOpen: bool};

let component = ReasonReact.reducerComponent("ModalSampleComponent");

let make = (_children) => {
  ...component,
  initialState: () => {isOpen: false},
  reducer: (action, _) =>
    switch (action) {
    | Open => ReasonReact.Update({isOpen: true})
    | Close => ReasonReact.Update({isOpen: false})
    },
  render: self => {
    <div>
      <Modal
        onClickContentOutside=(() => self.send(Close))
        hidden=(!self.state.isOpen)
        header=(
            <ModalHeader key="header" title=(<h3>(ReasonReact.string("MODAL!"))</h3>)>
              ...<button type_="button" className="close">
                    <span>("×" |> ReasonReact.string)</span>
                </button>
            </ModalHeader>
            )
            
        body=(
          <ModalBody key="body">
              ...<div>
                <p onClick=(_ => Js.Console.log("JS"))>(ReasonReact.string("LINE1LINE1LINE1LINE1LINE1LINE1LINE1LINE1LINE1sLINE1LINE1LINE1LINE1LINE1LINE1LINE1LINE1LINE1s"))</p>
                <span>(ReasonReact.string("LINE2"))</span>
              </div>
          </ModalBody>
          )
        footer=(
          <ModalFooter>
            ...<button onClick=(_ => self.send(Close)) type_="button" className="btn btn-primary">(ReasonReact.string("CLOSE"))</button>
          </ModalFooter>
        )
        size=(Modal.Large) />
        <button onClick=(_ => self.send(Open))>(ReasonReact.string("OPEN"))</button>
      </div>
  },
};

