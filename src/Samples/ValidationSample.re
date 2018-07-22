
type validationFailure = TextIsOverMaxLength;

let validateText = Validation.fromErrors((text) => 
    if (text |> String.length > 10) {
      [TextIsOverMaxLength]
    } else []
  );

type sampleRecordValidationFailure = InvalidName | InvalidAge;

type sampleRecord = {
  name: string,
  age: int,
};

let validateAge = Validation.fromErrors((age) => 
if (age >= 0) {
  []
} else [InvalidAge]
);

let validateName = Validation.fromErrors((name) => {
  if (name == "") {
    [InvalidName]
  } else []
});


let () = {
  /**
   * TODO (v) => v は identity的なのないっけ？ 
   */
  let _ = Validation.run(validateText, (v) => v, "success!");
}
