export function matchParentheses(expression: string) {
  const stack: string[] = [];
  let stringStart: null | number = null;
  for (let i = 0; i < expression.length; i++) {
    const c = expression[i]!;

    if (stringStart !== null) {
      if (c === '"') {
        if (stringStart === i - 1) {
          stack.push('"');
          stringStart = i;
        } else {
          stack.pop();
          if (stack.at(-1) !== '"') {
            stringStart = null;
          }
        }
      }
      continue;
    }

    switch (c) {
      case '"':
        stack.push('"');
        stringStart = i;
        break;
      case "{":
        stack.push("{");
        break;
      case "(":
        stack.push("(");
        break;
      case "[":
        stack.push("[");
        break;
      case "]":
        if (stack.at(-1) === "[") {
          stack.pop();
        } else {
          return false;
        }
        break;
      case ")":
        if (stack.at(-1) === "(") {
          stack.pop();
        } else {
          return false;
        }
        break;
      case "}":
        if (stack.at(-1) === "{") {
          stack.pop();
        } else {
          return false;
        }
        break;
    }
  }

  return stack.length === 0;
}

const input = `def example():
    string = "Unmatched bracket in string {"
    return (string)`;

console.log(
  matchParentheses(input)
);