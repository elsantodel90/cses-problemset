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


TT = int(input())
for tt in range(TT):
    y, x = map(int,input().split())
    layer = max(x,y)
    if layer % 2 == 0:
        x,y = y,x
    if y == layer:
        val = (layer-1)**2 + x
    else:
        val = layer**2 + 1 - y
    print(val)

