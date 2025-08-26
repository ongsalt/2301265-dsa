enum ParseError: Error {
  case invalidToken
}

func getPriority(_ symbol: SymbolType) -> (Int, Int) {
  // this look curse af, i shuold have just use rust
  return switch symbol {
  case .plus, .minus:
    (11, 10)
  case .slash, .star:
    (21, 20)
  default:
    (0, 0)
  }
}

class Parser {
  var tokens: [Token]

  init(tokens: [Token]) {
    self.tokens = Array(tokens.reversed())
  }

  func parse(priority: Int = 0) -> Result<Expression, ParseError> {
    var lhs = Expression.number("0")

    switch tokens.popLast() {
    case .number(let n):
      lhs = .number(n)
    case .symbol(let s):
      var expression: Expression!
      // arggghhhh, i want rustttttttt
      switch parse() {
      case .failure(let e):
        return .failure(e)
      case .success(let e):
        expression = e
      }

      switch s {
      case .leftParentheses:
        // lhs = .grouping(expression)
        lhs = expression
      case let op where op == .minus || op == .plus:
        lhs = .unary(op, expression)
      default:
        return .failure(.invalidToken)
      }

    default:
      return .failure(.invalidToken)
    }

    // default: "1 + 8 * 9"
    // "8 * 9 + 1"
    while true {
      if tokens.isEmpty {
        return .success(lhs)
      }

      guard case let .symbol(op) = tokens.popLast() else {
        return .failure(.invalidToken)
      }

      if op == .rightParentheses {
        break
      }

      if getPriority(op).1 < priority {
        tokens.append(.symbol(op))
        break
      }

      guard case let .success(rhs) = parse(priority: getPriority(op).0) else {
        return .failure(.invalidToken)
      }

      lhs = .binary(op, lhs, rhs)
    }

    return .success(lhs)
  }
}
