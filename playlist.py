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

CENTINELA = -1

n = int(input())
songs = list(readLineInts())
songs.append(CENTINELA)
s = set([CENTINELA])
b = 0
total = 0
for a in range(n):
    while songs[b] not in s:
        s.add(songs[b])
        b += 1
    total = max(total, b-a)
    assert b > a
    assert songs[a] in s
    s.remove(songs[a])
    a += 1
print(total)
