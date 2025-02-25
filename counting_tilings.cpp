#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int MOD = 1000000007;

// x+y*n
const int MAXN = 10;
int dp[3][1<<MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    
    assert(n <= MAXN);
    dp[(m*n)%3][0] = 1;
    dforn(y, m)
    dforn(x, n)
    {
        int index = x+y*n;
        forn(profile, 1<<n)
        {
            int newProfile = profile ^ (1<<x);
            dp[index%3][profile] = dp[(index+1)%3][newProfile];
            if (x+1 < n && ((profile >> x)&1) == 0 && ((profile >> (x+1))&1) == 0)
            {
                dp[index%3][profile] += dp[(index+2)%3][profile];
                dp[index%3][profile] %= MOD;
            }
        }
    }
    cout << dp[0][0] << "\n";
    
    return 0;
}
