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
    # Create a LP problem
    prob = LpProblem("MaximizeProfit", LpMaximize)

    # Define variables
    toy_vars = [LpVariable(f"x{i}", lowBound=0, cat="Integer") for i in range(n)]
    special_vars = [LpVariable(f"sp{i}", lowBound = 0, cat="Integer") for i in range(p)]

    # maximize total profit
    prob += lpSum(products[i][0] * toy_vars[i] for i in range(n)) + \
            lpSum(specials[i][3] * special_vars[i] for i in range(p)), "Total_Profit"
    
    prob += lpSum(toy_vars) + lpSum(special_vars)*3 <= max_toys

    # production limits for individual toys
    for i in range(n):
        prob += toy_vars[i] >= 0
        prob += toy_vars[i] <= products[i][1]

    # special packages must contain the required individual toys
    for i in range(p):
        for j in specials[i][:3]:
            prob += special_vars[i] <= toy_vars[j-1]

    # Solve the problem
    prob.solve()

    # Print the optimal values
    for v in prob.variables():
        print(v.name, "=", v.varValue)

    # Return the result
    return value(prob.objective)

def main():
    n, p, max_toys, products, specials = get_inputs()
    result = calculate(n, p, max_toys, products, specials)
    print(result)

main()
