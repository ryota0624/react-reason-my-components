type validator('e, 's) = Validator ('s => list('e));

let fromErrors = (getSubject, getErrors: 's => list('e)) => {
  Validator(getSubject @@ getErrors)
};

let all = (validators: list(validator('e, 's))): validator('e, 's) => {
  let allGetErrors = validators 
    |> List.map(validator => {
      switch (validator) {
      | Validator(getErrors) => getErrors
      };
    });

  let validateLogic = (subject) => 
      allGetErrors 
        |> List.map (getError => getError(subject)) 
        |> List.flatten;

  Validator(validateLogic)
};

let first = (validators: list(validator('e, 's))) => { 
  let allValidation = all(validators);

  let validateLogic = (subject) => 
    switch (allValidation) {
    | Validator(getErrors) => 
        try(getErrors(subject)) {
        | Failure(_) => []
        }
    };

  Validator(validateLogic);
}