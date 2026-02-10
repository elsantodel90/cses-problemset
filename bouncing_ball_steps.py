from math import lcm

TT = int(input())
for tt in range(TT):
    n,m,k = map(int, input().split())
    def pos(k,n):
        x = k%(2*(n-1))
        if x > n-1:
            x = 2*(n-1) - x
        return 1 + x
    x = pos(k,n)
    y = pos(k,m)
    l = lcm(n-1,m-1)
    base = (l//(n-1) + l//(m-1) - 1) * (k//l)
    k %= l
    print(x, y, base + k//(n-1) + k//(m-1))
