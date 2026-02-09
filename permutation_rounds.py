from math import gcd

def lcm(*v):
    ret = v[0]
    for i in range(1, len(v)):
        ret *= (v[i] // gcd(ret, v[i]))
    return ret

def payasos2(a):
    used = set()
    lens = set()
    for i in range(len(a)):
        if i not in used:
            x = i
            l = 0
            while x not in used:
                used.add(x)
                x = a[x]
                l += 1
            assert i == x
            lens.add(l)
    return lcm(*lens) % (10**9+7)

# grader
if __name__ == "__main__":
    import sys

    allTokens = iter(sys.stdin.read().split())
    def readToken():
        return next(allTokens)

    def main():
        N = int(readToken())
        A = [None]*(N)
        for i0 in range(N):
            A[i0] = int(readToken())-1
        returnedValue = payasos2(A)
        print(returnedValue)

    main()

