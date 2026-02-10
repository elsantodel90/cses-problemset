from math import gcd

TT = int(input())
for tt in range(TT):
    n,m = map(int, input().split())
    g = gcd(n-1,m-1)
    l = ((n-1)//g)*(m-1)
    f = ((n-2)//(2*g)) * ((m-2)//(2*g)) + ((n-2+g)//(2*g)) * ((m-2+g)//(2*g))
    print(2*l, 1 + l - f)
