indirect enum Expression {
  case number(String)
  case unary(SymbolType, Expression)
  case binary(SymbolType, Expression, Expression)
  // TODO: preserve grouping, number string
  case grouping(Expression)

  func asInOrderString() -> String {
    return switch self {
    case .number(let value):
      String(value)
    case .grouping(let expression):
      "(\(expression.asInOrderString()))"
    case .binary(let op, let left, let right):
      "(\(left.asInOrderString()) \(op.rawValue) \(right.asInOrderString()))"
      // "\(left.asInOrderString()) \(op.rawValue) \(right.asInOrderString())"
    case .unary(let op, let e):
      "\(op.rawValue) \(e.asInOrderString())"
    }
  }

  func asPostOrderString() -> String {
    return switch self {
    case .number(let value):
      String(value)
    case .binary(let op, let left, let right):
      "\(left.asPostOrderString()) \(right.asPostOrderString()) \(op.rawValue)"
    case .unary(let op, let e):
      "0 \(e.asPostOrderString()) \(op.rawValue)"
    case .grouping(let expression):
      expression.asPostOrderString()
    }
  }

  func asPreOrderString() -> String {
    return switch self {
    case .number(let value):
      String(value)
    case .binary(let op, let left, let right):
      "\(op.rawValue) \(left.asPreOrderString()) \(right.asPreOrderString())"
    case .unary(let op, let e):
      "\(op.rawValue) 0 \(e.asPreOrderString())"
    case .grouping(let expression):
      expression.asPreOrderString()
    }
  }
}
