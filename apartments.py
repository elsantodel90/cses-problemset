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

from heapq import heappush, heappop

INF = 10**18

def readLineInts():
    return map(int,input().split())
n,m,k = readLineInts()
intervals = [(x-k, x+k) for x in readLineInts()]    
intervals.sort()
total = 0
nextInter = 0
heap = []
for apartment in sorted(readLineInts()):
    while nextInter < n and intervals[nextInter][0] <= apartment:
        heappush(heap, intervals[nextInter][1])
        nextInter += 1
    while heap and heap[0] < apartment:
        heappop(heap)
    if heap:
        heappop(heap)
        total += 1
print(total)
