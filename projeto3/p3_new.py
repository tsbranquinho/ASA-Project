from pulp import LpMaximize, LpProblem, LpVariable, lpSum, GLPK, value

# Create the optimization problem
prob = LpProblem("maximize_profit", LpMaximize)

# Read input
num_toys, num_specials, max_toys = map(int, input().split())
maxtoys = 0

toys_info = []
toy_vars = []
for i in range(num_toys):
    toys_info.append(list(map(int, input().split())))
    toy_vars.append(LpVariable(name=f"x{i}", lowBound=0, upBound=toys_info[i][1], cat="Integer"))
    maxtoys += toy_vars[i]

special_vars = []
specials_info = []
for i in range(num_specials):
    specials_info.append(list(map(int, input().split())))
    minimum = min(toys_info[0][1],toys_info[1][1],toys_info[2][1])
    special_vars.append(LpVariable(name=f"s{i}", lowBound=0, upBound= minimum, cat="Integer"))
    maxtoys += special_vars[i] * 3
    for j in range(3):
        toy_vars[specials_info[i][j]- 1] += special_vars[i]

# Restriction
prob += maxtoys <= max_toys 

# Constraint: production capacity for each toy
for i in range(num_toys):
    prob += lpSum(toy_vars[i]) <= toys_info[i][1], f"Capacity_Toy_{i}"

# Solve the problem
prob.solve(GLPK(msg=0))

# Obtain the value of the objective function (maximum profit)
max_profit = int(value(prob.objective))

print(max_profit)