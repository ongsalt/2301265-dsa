enum ParseError: Error {
  case invalidToken
}

func getPriority(_ symbol: SymbolType) -> (Int, Int) {
  // this look curse af, i shuold have just use rust
  return switch symbol {
  case .plus, .minus:
    (10, 11)
  case .slash, .star:
    (20, 21)
  default:
    fatalError()
  }
}

//(10-2) * 8 / (3+1) + 5

class Parser {
  var tokens: [Token]

  init(tokens: [Token]) {
    self.tokens = Array(tokens.reversed())
  }

  func parse(priority: Int = 0) -> Result<Expression, ParseError> {
    // print("Enter with \(tokens.last)")
    var lhs = Expression.number("0")

    switch tokens.popLast() {
    case .number(let n):
      lhs = .number(n)
    case .symbol(let s):
      var expression: Expression!
      // arggghhhh, i want rustttttttt
      switch parse(priority: 0) {
      case .failure(let e):
        return .failure(e)
      case .success(let e):
        expression = e
      }

      switch s {
      case .leftParentheses:
        // lhs = .grouping(expression)
        lhs = expression
        _ = tokens.popLast()
      case let op where op == .minus || op == .plus:
        lhs = .unary(op, expression)
      default:
        return .failure(.invalidToken)
      }

    default:
      return .failure(.invalidToken)
    }

    // print(lhs)

    // default: "1 + 8 * 9"
    // "8 * 9 + 1"
    // (10-2) * 8 / (3+1) + 5
    while true {
      if tokens.isEmpty {
        break
      }

      guard case let .symbol(op) = tokens.last else {
        return .failure(.invalidToken)
      }

      if op == .rightParentheses {
        break
      }

      let p = getPriority(op)

      if priority > p.0 {
        break
      }

      _ = tokens.popLast()

      guard case let .success(rhs) = parse(priority: p.1) else {
        return .failure(.invalidToken)
      }

      lhs = .binary(op, lhs, rhs)
    }

    // print("Exit with \(lhs.asInOrderString())")
    return .success(lhs)
  }
}
