INF = 1000000000000000000

n = int(input())
x = list(map(int, input().split())) + [INF]
dif = [x[i+1] - x[i] for i in range(n)]
total = 0
for i in range(n-1):
    needed = max(0, -dif[i])
    dif[i+1] -= needed
    total += needed
print(total)
