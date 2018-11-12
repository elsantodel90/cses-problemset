# MAGIC CODEFORCES PYTHON FAST IO
import atexit
import io
import sys

_INPUT_LINES = sys.stdin.read().splitlines()
input = iter(_INPUT_LINES).__next__
_OUTPUT_BUFFER = io.StringIO()
sys.stdout = _OUTPUT_BUFFER

@atexit.register
def write():
    sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())
# END OF MAGIC CODEFORCES PYTHON FAST IO

def readLineInts():
    return map(int,input().split())

n,x = readLineInts()
p = sorted(readLineInts())
a = 0
b = n
total = 0
while b - a > 1:
    if p[a] + p[b-1] <= x:
        a += 1
    total += 1
    b -= 1
assert(b-a in [0,1])
if b-a == 1:
    total += 1
print(total)
