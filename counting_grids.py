n=int(input())
M=10**9+7
print(sum(pow(2,n*n-x+1>>x%3,M)for x in[2,3,4])%M)
