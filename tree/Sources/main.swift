// let input = "1 + 8"
// let input = "1 + 8 * 9"
// let input = "(1 + 8) * 9"
// let input = "8 * 9 + 1"
// [8, "*", 9, "+", 1]

// let input = "5 + 3 - 2"
let input = "2.5 + 3 * -(4 - 2)"

let lexer = Lexer(input: input)
let tokens = try lexer.lex().get()

let parser = Parser(tokens: tokens)
let expression = try parser.parse().get()

// debugPrint(tokens)
// debugPrint(expression)

let postOrderString = expression.asPostOrderString()

print(
  postOrderString,
  expression.asPreOrderString(),
  expression.asInOrderString(),
  separator: "\n"
)
print(evaluate(expression))

let postOrderTokens = try Lexer(input: postOrderString).lex().get()
// print(postOrderTokens)
print(
  evaluatePostOrderNotation(tokens: postOrderTokens)
)
