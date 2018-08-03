export function execute(n) {
  return n + 100;
}

export function executeNullable(n) {
  return 1000;
}


export function executePromise(n) {
  return Promise.resolve(n + 100);
}

export function executeArgObj(obj) {
  return {...obj, a: 100};
}