from pulp import LpProblem, LpVariable, lpSum, value, LpMaximize, GLPK

def get_inputs():
    base = list(map(int, input().split()))
    n, p, max_toys = base[0], base[1], base[2]
    products = []
    specials = []
    for _ in range(n):
        products.append(list(map(int, input().split())))
    for _ in range(p):
        specials.append(list(map(int, input().split())))
    return n, p, max_toys, products, specials

def calculate(n, p, max_toys, products, specials):
    # create a LP problem
    prob = LpProblem("MaximizeProfit", LpMaximize)
    toy_vars = []
    special_vars = []
    toy_objective = []
    special_objective = []
    packs = [[] for _ in range(n)]

    for i in range(p):
        special_vars += [LpVariable(f"sp{i}", lowBound = 0, cat="Integer")]
        special_objective += [specials[i][3] * special_vars[i]]
        for j in range(3):
            packs[specials[i][j] - 1].append(special_vars[i])
    for i in range(n):
        toy_vars += [LpVariable(f"x{i}", lowBound=0, cat="Integer")]
        toy_objective += [products[i][0] * toy_vars[i]]
        prob += toy_vars[i] >= 0
        prob += lpSum(packs[i]) <= products[i][1] - toy_vars[i]
    prob += lpSum(toy_vars) + lpSum(special_vars)*3 <= max_toys
    prob += lpSum(toy_objective) + lpSum(special_objective), "Total_Profit"

    # Constraints:
    # limit the number of toys
    # limit the number of toys in each special pack
    # account for all special packs
    #for i in range(n):
    #    packs = []
    #    for j in range(p):
    #        if i+1 in specials[j][:3]:
    #            packs.append(special_vars[j])
    #    prob += lpSum(packs) <= products[i][1] - toy_vars[i]

    # limit the total number of toys

    # solve the problem
    prob.solve(GLPK(msg=0))

    # return the result
    return value(prob.objective)

def main():
    n, p, max_toys, products, specials = get_inputs()
    result = calculate(n, p, max_toys, products, specials)
    print(result.__int__())

main()