n = int(input())
total = 0
for bitNumber in range(64,-1,-1):
    bit = 1<<bitNumber
    if bit & n:
        total += (bit * bitNumber) // 2
        n -= bit
        total += n + 1
print(total)
