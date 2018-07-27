type validationFailure =
  | TextIsOverMaxLength
  | TextIsEmpty;

let validateText =
  Validation.fromErrors(text =>
    if (text |> String.length > 10) {
      [TextIsOverMaxLength];
    } else {
      [];
    }
  );

type sampleRecordValidationFailure =
  | InvalidName
  | InvalidAge;

type sampleRecord = {
  name: string,
  age: int,
};

let validateAge = getAge =>
  Validation.fromErrors(record =>
    if (getAge(record) >= 0) {
      [];
    } else {
      [InvalidAge];
    }
  );

let validateName = getName =>
  Validation.fromErrors(record =>
    if (getName(record) == "") {
      [InvalidName];
    } else {
      [];
    }
  );

let ifEmptyString = (getString, errors) =>
  Validation.fromErrors(source =>
    if (getString(source) == "") {
      errors;
    } else {
      [];
    }
  );

let () = {
  /**
   * TODO (v) => v は identity的なのないっけ？
   */
  let _ = Validation.run(validateText, "success!");

  let _ =
    Validation.run(
      Validation.all([ifEmptyString(v => v, [TextIsEmpty]), validateText]),
      "",
    );

  let _ =
    Validation.run(
      Validation.all([validateAge(r => r.age), validateName(r => r.name)]),
      {age: 30, name: "dad"},
    );
  ();
};
