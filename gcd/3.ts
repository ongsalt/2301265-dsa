export function gcd(m: number, n: number) {
  if (n === 0) {
    return m;
  }
  if (m === 0) {
    return n;
  }
  if (m > n) {
    return gcd(m % n, n);
  }
  if (m < n) {
    return gcd(m, n % m);
  }
  return m;
}


console.log(gcd(111, 234));
