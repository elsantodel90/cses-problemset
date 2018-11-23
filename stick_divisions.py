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

def solve():
    INF = 10**20

    x,n = map(int,input().split())
    d = list(map(int,input().split()))
    d.sort()
    d.append(INF)

    q = []
    a = b = 0
    ret = 0
    for steps in range(n-1):
        newElement = 0
        for items in range(2):
            if b == len(q) or d[a] < q[b]:
                newElement += d[a]
                a += 1
            else:
                newElement += q[b]
                b += 1
        ret += newElement
        q.append(newElement)
    print(ret)
    
solve()
