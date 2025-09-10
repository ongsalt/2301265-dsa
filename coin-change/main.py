from memo import memo

amount = int(input())
coin_types = [int(i) for i in input().split()]


def bottom_up():
    solutions = []
    for a in range(amount + 1):
        minimum = float('inf')
        for coin in coin_types:
            rest = a - coin
            if rest == 0:
                minimum = 1
            elif rest > 0 and len(solutions) > rest:
                # print(f"{rest=} {coin=}")
                minimum = min(minimum, solutions[rest] + 1)
        solutions.append(minimum)

    print(solutions)
    print(solutions[amount])
    return solutions[amount]


def _get_minimum(amount: int):
    minimum = []
    for coin in coin_types:
        rest = amount - coin
        if rest == 0:
            return [coin]
        if rest > 0:
            coins = get_minimum(rest)
            if len(coins) + 1 < len(minimum) or not minimum:
                minimum = [*coins, coin]

    return minimum

get_minimum = memo(_get_minimum)

def _get_all(amount: int):
    out = []
    for coin in coin_types:
        rest = amount - coin
        if rest == 0:
            return [[coin]]
        if rest > 0:
            solutions = get_all(rest)
            for solution in solutions:
                # print(f"{solution=}")
                out.append([*solution, coin])

    return out

get_all = memo(_get_all)

print(get_minimum(amount))
# print(get_all(amount))
