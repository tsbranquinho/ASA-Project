from pulp import LpProblem, LpVariable, lpSum, value, LpMaximize

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

    # define variables
    toy_vars = [LpVariable(f"x{i}", lowBound=0, cat="Integer") for i in range(n)]
    special_vars = [LpVariable(f"sp{i}", lowBound = 0, cat="Integer") for i in range(p)]

    # maximize total profit
    prob += lpSum(products[i][0] * toy_vars[i] for i in range(n)) + \
            lpSum(specials[i][3] * special_vars[i] for i in range(p)), "Total_Profit"

    # Constraints:
    # limit the number of toys
    # limit the number of toys in each special pack
    # account for all special packs
    for i in range(n):
        packs = []
        for j in range(p):
            if i+1 in specials[j][:3]:
                packs.append(special_vars[j])
        prob += lpSum(packs) <= products[i][1] - toy_vars[i]
        prob += toy_vars[i] >= 0

    # limit the total number of toys
    prob += lpSum(toy_vars) + lpSum(special_vars)*3 <= max_toys

    # solve the problem
    prob.solve()

    for constraint_name, constraint in prob.constraints.items():
        print(f"Constraint {constraint_name}: {constraint}")

    # print the optimal values
    for v in prob.variables():
        print(v.name, "=", v.varValue)

    # return the result
    return value(prob.objective)

def main():
    n, p, max_toys, products, specials = get_inputs()
    result = calculate(n, p, max_toys, products, specials)
    print(result)

main()
