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

t = int(input())
for caseNumber in range(t):
    n = int(input())
    ret = 0
    for x in map(int, input().split()):
        ret ^= x%4
    print("first" if ret != 0 else "second")
