n,m = map(int, input().split())

MOD = 10**9+7

def factorial(n):
    ret = 1
    for i in range(1,n+1):
        ret = (ret*i)%MOD
    return ret

def inverse(x):
    return pow(x,-1,MOD)

def choose(n,k):
    return (factorial(n) * inverse(factorial(k)) * inverse(factorial(n-k))) % MOD

print(choose(n+m-1,m))
