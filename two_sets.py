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

n = int(input())
if n % 4 in [0,3]:
    print("YES")
    a = []
    b = []
    start, end = 1, n
    if n % 4 == 3:
        a = [1,2]
        b = [3]
        start = 4
    for i in range((end - start + 1) // 4):
        a.extend((start + 2*i, end - 2*i))
        b.extend((start + 2*i + 1, end - 2*i - 1))
    for s in (a,b):
        print(len(s))
        print(" ".join(map(str, s)))
    
else:
    print("NO")
