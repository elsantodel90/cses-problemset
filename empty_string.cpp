#include <iostream>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

typedef long long tint;

const tint MOD = 1000000007;

const int MAXN = 512;

tint dp[MAXN][MAXN];
tint binom[MAXN][MAXN];

void pascal()
{
    forn(n,MAXN)
    {
        binom[n][0] = binom[n][n] = 1;
        forsn(k,1,n)
            binom[n][k] = (binom[n-1][k-1] + binom[n-1][k])%MOD;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pascal();
    string s; cin >> s;
    const int N = int(s.size());
    forn(i,N+1)
        dp[i][i] = 1;
    forn(j,N+1)
    dforn(i,j)
    {
        tint &ret = dp[i][j] = 0;
        forsn(k,i+1,j)
        if (s[i] == s[k])
            ret = (ret + binom[(j-i)/2][(j-k-1)/2]*((dp[i+1][k] * dp[k+1][j])%MOD)) % MOD;
    }
    cout << dp[0][N] << endl;
    return 0;
}
