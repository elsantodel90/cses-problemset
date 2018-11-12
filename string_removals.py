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

MODU = 10**9+7

s = input()
lastOccurence = [0] * 26
dp = [0] * (len(s)+2)
dp[1] = 1
for i,c in enumerate(s):
    letterIndex = ord(c)-ord('a')
    dp[i+2] = (2 * dp[i+1] - dp[lastOccurence[letterIndex]]) % MODU
    lastOccurence[letterIndex] = i+1
    
print((dp[len(s)+1] - 1) % MODU)
