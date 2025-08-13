function getPrimeFactors(n: number): number[] {
  if (n <= 1) return [];

  const sieve = new Array(n + 1).fill(true) as boolean[];
  sieve[0] = sieve[1] = false;

  for (let i = 2; i * i <= n; i++) {
    if (sieve[i]) {
      for (let j = i * i; j <= n; j += i) {
        sieve[j] = false;
      }
    }
  }

  const primeFactors: number[] = [];
  let num = n;

  for (let i = 2; i <= num; i++) {
    if (sieve[i]) {
      while (num % i === 0) {
        primeFactors.push(i);
        num /= i;
      }
    }
  }

  return primeFactors;
}

function findCommon(a: number[], b: number[]): number[] {
  const aFreq = new Map<number, number>();
  const bFreq = new Map<number, number>();

  for (const num of a) {
    aFreq.set(num, aFreq.get(num) ?? 0 + 1);
  }

  for (const num of b) {
    bFreq.set(num, bFreq.get(num) ?? 0 + 1);
  }

  const out: number[] = [];
  for (const [num, freq] of aFreq.entries()) {
    let amount = Math.min(bFreq.get(num) ?? 0, freq);
    while (amount > 0) {
      out.push(num);
      amount -= 1;
    }
  }

  return out;
}

export function gcd(m: number, n: number) {
  const mPrimeFactors = getPrimeFactors(m);
  const nPrimeFactors = getPrimeFactors(n);
  const common = findCommon(nPrimeFactors, mPrimeFactors);
  return common.reduce((prod, n) => prod * n, 1);
}

// console.log(gcd(111, 234));
// console.log(gcd(60, 225));