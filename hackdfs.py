
N = 10**5

mid = N//2

edges = []

for i in range(1, N):
    edges.append((i,i+1))

for j in range(mid+2, N+1):
    edges.append((mid,j))

print(N, len(edges))
for a,b in edges:
    print(b,a)
