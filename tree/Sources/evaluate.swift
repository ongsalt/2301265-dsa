enum EvaluateError: Error {
  case invalidToken
  case invalidOperator
  case invalidNumber
  case empty
}

func evaluate(_ expression: Expression) -> Float64 {
  // oh god, i hate this syntax
  return switch expression {
  case .number(let value): Float64(value)!
  case .binary(let op, let left, let right):
    switch op {
    case .plus: evaluate(left) + evaluate(right)
    case .minus: evaluate(left) - evaluate(right)
    case .slash: evaluate(left) / evaluate(right)
    case .star: evaluate(left) * evaluate(right)
    default: fatalError("\(op) is not a binary op")
    }
  case .unary(let op, let e):
    switch op {
    case .plus: evaluate(e)
    case .minus: -evaluate(e)
    case .star: fatalError("sorry we dont do pointer here")
    default: fatalError("\(op) is not a unary op")
    }
  case .grouping(let expression): evaluate(expression)
  }
}
func evaluatePostOrderNotation(tokens: [Token]) -> Result<Float64, EvaluateError> {
  var stack: [Float64] = []

  for token in tokens {
    switch token {
    case .number(let value):
      guard let f = Float64(value) else {
        return .failure(.invalidNumber)
      }
      stack.append(f)

    case .symbol(let s):
      guard let rhs = stack.popLast() else { return .failure(.invalidToken) }
      guard let lhs = stack.popLast() else { return .failure(.invalidToken) }

      let result: Float64? =
        switch s {
        case .plus: lhs + rhs
        case .minus: lhs - rhs
        case .star: lhs * rhs
        case .slash: lhs / rhs
        default: nil
        }

      if result == nil {
        return .failure(.invalidOperator)
      }

      stack.append(result!)
    }
  }

  if stack.count != 1 {
    return .failure(.empty)  // actually wtf
  }

  return .success(stack[0])
}
