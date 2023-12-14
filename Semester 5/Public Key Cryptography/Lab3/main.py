import random

def millerTest(d, n):
    """
    miller rabin algorithm
    :param d: odd number d*2^r = n-1, r >= 1
    :param n: the number to be checked
    :return: true, n prime; false, n composite
    """
    a = 2 + random.randint(1, n - 4)  # base a (2, n-2]
    x = pow(a, d, n)  # compute a^d % n

    # if primme return true
    if x == 1 or x == n - 1:
        return True

    # x^2, d*2 while:
    # d does not reach n-1
    # (x^2) % n is not 1 => composite
    # (x^2) % n is not n-1 => prime
    while d != n - 1:
        x = (x * x) % n
        d *= 2  # n-1 = 2^r *d

        if x == 1:
            return False
        if x == n - 1:
            return True

    # Return composite
    return False


def isPrime(n, k):
    """
    checks if n is prime
    :param n: the number to be checked
    :param k: higher k => more accuracy
    :return: true, n prime; false, n composite
    """
    if n <= 1 or n == 4:
        return False
    if n <= 3:
        return True

    # odd number d such that n-1 can be written as d*2^r
    d = n - 1
    while d % 2 == 0:
        d //= 2

    # miller-rabin test k times
    # if all iterations pass, the number is prime
    for i in range(k):
        if not(millerTest(d, n)):
            return False
    return True


k = 4

for n in range(1, 101):
    if isPrime(n, k):
        print(n)