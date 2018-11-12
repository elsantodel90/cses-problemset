def f(n):
    if n % 2 == 0:
        return n // 2
    else:
        return 3*n+1

def values(n):
    while n != 1:
        yield n
        n = f(n)
    yield 1

n = int(input())
print(" ".join(map(str, values(n))))
