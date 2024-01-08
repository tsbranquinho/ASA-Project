from pulp import LpProblem, LpVariable, lpSum, value, LpMaximize, GLPK, PULP_CBC_CMD as CBC
import sys

def get_inputs():
    n, p, max_toys = map(int, sys.stdin.readline().split())
    products = [list(map(int, sys.stdin.readline().split())) for _ in range(n)]
    specials = [list(map(int, sys.stdin.readline().split())) for _ in range(p)]
    return n, p, max_toys, products, specials

def calculate(n, p, max_toys, products, specials):
    prob = LpProblem("MaximizeProfit", LpMaximize)
    packs = [[] for _ in range(n)]
    toy_vars = [LpVariable(f"x{i}", lowBound=0, cat="Integer") for i in range(n)]
    toy_objective = [products[i][0] * toy_vars[i] for i in range(n)]
    special_vars = [LpVariable(f"sp{i}", lowBound=0, cat="Integer") for i in range(p)]
    special_objective = [specials[i][3] * special_vars[i] for i in range(p)]
    # restrictions for specials
    for i in range(p):
        for j in range(3):
            packs[specials[i][j] - 1].append(special_vars[i])
    # restrictions for toys
    for i in range(n):
        prob += toy_vars[i] >= 0
        prob += lpSum(packs[i]) <= products[i][1] - toy_vars[i]

    # restrictions for total toys
    prob += lpSum(toy_vars) + lpSum(special_vars)*3 <= max_toys

    # maximize profit
    prob += lpSum(toy_objective) + lpSum(special_objective), "Total_Profit"

    prob.solve(CBC(msg = 0, presolve=False))
    return int(value(prob.objective))

def main():
    n, p, max_toys, products, specials = get_inputs()
    result = calculate(n, p, max_toys, products, specials)
    print(result)

main()