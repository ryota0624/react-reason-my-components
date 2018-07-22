type validator('e, 's) = pri Validator ('s => list('e));

let fromErrors: ('subject => list('e)) => validator('e, 'subject);

let all: (list(validator('e, 's))) => validator('e, 's);

let first: (list(validator('e, 's))) => validator('e, 's);

let run: (validator('e, 'subject), 'source => 'subject, 'source) => list('e);