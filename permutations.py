n = int(input())
if 1 < n < 4:
    print("NO SOLUTION")
else:
    pares   = list(range(2,n+1,2))
    impares = list(range(1,n+1,2))
    print(" ".join(map(str, pares + impares)))
