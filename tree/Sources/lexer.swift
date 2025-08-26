enum SymbolType: Character {
  case leftParentheses = "("
  case rightParentheses = ")"
  case plus = "+"
  case minus = "-"
  case star = "*"
  case slash = "/"
}

enum Token {
  case symbol(SymbolType)
  case number(String)
}

struct InvalidCharacterError {
  var position: UInt
  var character: Character
}

enum LexerError: Error {
  case invalidCharacter(InvalidCharacterError)
}

class Lexer {
  let input: String

  init(input: String) {
    self.input = input
  }

  func lex() -> Result<[Token], LexerError> {
    var tokens: [Token] = []

    for cursor: Int in 0..<(input.count) {
      let index = input.index(input.startIndex, offsetBy: cursor)
      let c = input[index]

      if let symbol = SymbolType(rawValue: c) {
        tokens.append(.symbol(symbol))
        continue
      }

      if c == " " {
        continue
      }

      var previous = ""
      if case let .number(num) = tokens.last {
        let previousIndex = input.index(input.startIndex, offsetBy: cursor - 1)
        let previousCharacter = input[previousIndex]
        if previousCharacter != " " {
          previous = num
          _ = tokens.popLast()
        }
      }

      // TODO: check if c is 0-9 and .
      tokens.append(.number("\(previous)\(c)"))
    }

    return .success(tokens)
  }
}
