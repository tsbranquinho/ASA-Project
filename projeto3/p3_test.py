from pulp import LpProblem, LpVariable, lpSum, value, LpMaximize, GLPK
import sys

def get_inputs():
    n, p, max_toys = map(int, sys.stdin.readline().split())
    return n, p, max_toys

def calculate(n, p, max_toys):
    prob = LpProblem("MaximizeProfit", LpMaximize)
    packs = {}
    max_each_toy = []
    toy_vars = []
    special_vars = []
    toy_objective = 0
    special_objective = 0

    for i in range(n):
        product = list(map(int, sys.stdin.readline().split()))
        max_each_toy.append(product[1])
        toy_vars.append(LpVariable(f"x{i}", lowBound=0, upBound= product[1], cat="Integer"))
        toy_objective += product[0] * toy_vars[i]

    for i in range(p):
        special = list(map(int, sys.stdin.readline().split()))
        special_vars.append(LpVariable(f"sp{i}", lowBound=0, cat="Integer"))
        special_objective += special[3] * special_vars[i]
        for j in range(3):
            try:
                packs[special[j] - 1] += special_vars[i]
            except KeyError:
                packs[special[j] - 1] = special_vars[i]
    
    # restrictions for toys
    for i in range(n):
        try:
            prob += packs[i] <= max_each_toy[i] - toy_vars[i]
        except KeyError:
            pass

    # restrictions for total toys
    prob += lpSum(toy_vars) + lpSum(special_vars)*3 <= max_toys

    # maximize profit
    prob += toy_objective + special_objective, "Total_Profit"

    prob.solve(GLPK(msg = 0))
    return int(value(prob.objective))

def main():
    n, p, max_toys = get_inputs()
    result = calculate(n, p, max_toys)
    print(result)

main()