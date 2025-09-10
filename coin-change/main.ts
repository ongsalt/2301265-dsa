import { memo } from "../lib/memo";

async function parse(file: string) {
  const [a, c] = (await Bun.file(file).text()).split('\n');
  return {
    amount: parseInt(a),
    coinTypes: c.split(" ").map(it => parseInt(it))
  };
}


function bottomUp(amount: number, coinTypes: number[]): number[] {
  const solutions: number[][] = [[]];

  for (let a = 1; a <= amount; a++) {
    let best: number[] = [];
    for (const coin of coinTypes) {
      const rest = a - coin;
      const restSolutions = solutions[rest];

      if (rest == 0) {
        best = [coin];
        break;
      }
      if (rest > 0 && (restSolutions.length + 1 < best.length || best.length == 0)) {
        best = [...restSolutions, coin];
      }
    }
    solutions.push(best);
  }

  return solutions[amount];
}

const getMinimum = memo((amount: number, coinTypes: number[]): number[] => {
  let minimum: number[] | null = null;
  for (const coin of coinTypes) {
    const rest = amount - coin;
    if (rest === 0) {
      return [coin];
    }
    if (rest > 0) {
      const coins = getMinimum(rest, coinTypes);
      if (coins.length > 0) {
        const candidate = [...coins, coin];
        if (!minimum || candidate.length < minimum.length) {
          minimum = candidate;
        }
      }
    }
  }
  return minimum ?? [];
});

const getAll = memo((amount: number, coinTypes: number[]): number[][] => {
  const out: number[][] = [];
  for (const coin of coinTypes) {
    const rest = amount - coin;
    if (rest === 0) {
      return [[coin]];
    }
    if (rest > 0) {
      const solutions = getAll(rest, coinTypes);
      for (const solution of solutions) {
        out.push([...solution, coin]);
      }
    }
  }
  return out;
});


const { amount, coinTypes } = await parse("./testcases/5.14.txt");

console.log(bottomUp(amount, coinTypes));
console.log(getMinimum(amount, coinTypes));
console.log(getAll(amount, coinTypes));

export { };