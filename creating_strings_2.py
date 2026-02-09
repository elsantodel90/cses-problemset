h = [0] * 26
for x in input():
    h[ord(x)-ord('a')] += 1

MOD = 10**9+7
n = sum(h)
f = [0] * (n+1)
f[0] = 1
for i in range(n):
    f[i+1] = ((i+1)*f[i])%MOD

ret = f[n]
for x in h:
    ret = (ret * pow(f[x],-1,MOD)) % MOD

print(ret)
