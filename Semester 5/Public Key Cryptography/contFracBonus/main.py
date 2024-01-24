import math

def factorize_n(n, iterations):
    # init
    b = []
    a = []
    x = []
    b2 = []

    # b0 a0
    b.append(int(math.sqrt(n)))
    a.append(int(math.sqrt(n)))
    x.append(math.sqrt(n) - a[0])

    # Calculate b2_0 mod n
    b2.append(-(n - ((a[0] ** 2) % n)))

    for i in range(1, iterations):
        if i == 1:
            a.append(int(1/x[i-1]))
            x.append((1/x[i-1])-a[i])
            b.append((a[i]*b[i-1]+1)% n)
            y = (b[i]**2) % n
            if y > 7000 and y < 7769:
                y = -(n - y)
            elif y > 7769:
                y = y % n
            b2.append(y)
        else:
            a.append(int(1 / x[i - 1]))
            x.append((1 / x[i - 1]) - a[i])
            b.append((a[i]*b[i-1]+b[i-2])% n)
            y = (b[i] ** 2) % n
            if y > 7000 and y < 7769:
                y = -(n - y)
            elif y > 7769:
                y = y % n
            b2.append(y)

    print("i   ai   bi   b2i mod n")
    print("------------------------")
    for i in range(len(a)):
        print(f"{i}   {a[i]}   {b[i]}   {b2[i]}")




# Example usage with n = 9073 and 5 iterations
n = 7769
iterations = 15
result_table = factorize_n(n, iterations)


