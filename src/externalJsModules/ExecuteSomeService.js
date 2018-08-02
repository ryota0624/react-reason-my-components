export function execute(n) {
  return n + 100;
}


export function executePromise(n) {
  return Promise.resolve(n + 100);
}