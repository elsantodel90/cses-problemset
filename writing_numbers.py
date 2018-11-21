def countOnes(n):
    total = 0
    for digitNumber in range(19,-1,-1):
        pow10 = 10**digitNumber
        digit = n // pow10
        total += digit * (10**max(digitNumber-1,0) * digitNumber)
        n %= pow10
        if digit == 1:
            total += n+1
        elif digit > 1:
            total += pow10
    return total
    
n = int(input())
a = 0
b = 10**20
while b-a > 1:
    c = (a+b)//2
    if countOnes(c) <= n:
        a = c
    else:
        b = c
print(a)
