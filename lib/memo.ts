export function memo<TArgs extends any[], TRet>(fn: (...args: TArgs) => TRet): (...args: TArgs) => TRet {
  const cache = new Map<string, TRet>();
  return (...args) => {
    const key = JSON.stringify(args); // bruh
    if (cache.has(key)) {
      return cache.get(key)!;
    }
    const ret = fn(...args);
    cache.set(key, ret);
    return ret;
  };
}

const factorial = memo((n: number): number => {
  if (n === 0 || n === 1) {
    return 1;
  }

  console.log("fallthrough")
  return n * factorial(n - 1);
});

// console.log(factorial(8))
// console.log(factorial(9))
// console.log(factorial(9))
// console.log(factorial(9))
// console.log(factorial(9))
