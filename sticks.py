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
p = list(map(int, input().split()))
p.sort()
median = p[len(p)//2]
print(sum(abs(x-median) for x in p))
