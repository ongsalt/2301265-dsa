// INCOMPLTETE, see my lox parser instead


const prioty = {
  "+": 0,
  "-": 0,
  "*": 1,
  "/": 1
};

const isOp = (c: string) => c in prioty;

// 

// "" sdfhusdfu ""
// ("") sdfhusdfu ("")
// ("" sdfhusdfu "")

type Token = "*" | "/" | "+" | "-" | number;

function parse(expression: string): Token[] {
  const tokens: Token[] = [];

  for (const c of expression) {
    switch (c) {
      case "+":
        tokens.push("+");
        break;
      case "-":
        tokens.push("-");
        break;
      case "*":
        tokens.push("*");
        break;
      case "/":
        tokens.push("/");
        break;
      default:
        const top = tokens.pop();
        let prev = 0;
        if (typeof top === "string") {
          tokens.push(top);
        } else if (top !== undefined) {
          prev = top;
        }
        const num = (prev ?? 0) * 10 + parseInt(c);
        tokens.push(num);
    }
  }

  return tokens;
}

function apply() {
  
}

export function evaluate(expression: string) {
  const tokens = parse(expression);
  console.log(tokens);

  let ops: Exclude<Token, number>[] = [];
  let nums: number[] = [];

  for (const c of tokens) {
    switch (c) {
      case "+":
      case "-":
        if (["+", "-"].includes(ops.pop() as any)) {
          const res = nums.pop()!;
        }
        ops.push(c);
        break;

      case "*":
      case "/":
        ops.push(c);
        // break;
        // break;
        // break;
        break;
      default:
        nums.push(c);
        break;
    }
  }
}

evaluate("6*89+12");