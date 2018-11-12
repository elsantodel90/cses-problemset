def repetitionSize(s):
    prev = None
    ret = 0
    total = 0
    for c in s:
        if c == prev:
            total += 1
        else:
            total = 1
        ret = max(ret, total)
        prev = c
    return ret

s = input()
print(repetitionSize(s))
