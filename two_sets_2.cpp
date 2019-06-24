#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

typedef long long tint;

const int MAXN = 512;
const int MAX_SUM = 151000;

const int MOD = 1000000007;
const int INV2 = (MOD+1)/2;

int dp[MAX_SUM];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    const int totalSum = (n*(n+1))/2;
    if (totalSum % 2 != 0)
        cout << "0\n";
    else
    {
        dp[0] = 1;
        forn(i,n)
        {
            int maxs = min(totalSum/2, (n*(n+1))/2);
            dforsn(s,i, maxs+1)
            {
                dp[s] += dp[s - i];
                dp[s] -= MOD * (dp[s] >= MOD);
            }
        }
        cout << (tint(dp[totalSum/2]) * tint(INV2)) % MOD << "\n";
    }
    return 0;
}
