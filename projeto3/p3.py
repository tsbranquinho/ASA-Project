def get_inputs():
    base = list(map(int, input().split()))
    n, p, max = base[0], base[1], base[2]
    products = []
    specials = []
    for _ in range(n):
        products.append(list(map(int, input().split())))
    for _ in range(p):
        specials.append(list(map(int, input().split())))
    return n, p, max, products, specials

def calculate():
    pass

def main():
    n, p, max, products, specials = get_inputs()
    result = calculate()
    print(result)

main()