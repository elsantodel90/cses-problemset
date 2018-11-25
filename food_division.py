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

import itertools

def solve():
    n = int(input())
    a = map(int, input().split())
    b = map(int, input().split())
    delta = map(lambda x,y : x-y,a,b)
    partialSums = sorted(itertools.accumulate(delta))
    median = partialSums[n//2]
    print(sum(abs(median - x) for x in partialSums))
    
solve()
