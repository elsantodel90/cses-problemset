#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <queue>
#include <cassert>
#include <map>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define all(c) (c).begin(), (c).end()

typedef long long tint;

const int INF = 1000000000;

const int MAX_N = 128;
const int MAX_X = 1100000;

const int MOD = 1000000007;

int dp[MAX_N][MAX_X];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, X;
    cin >> n >> X;
    vector<int> v(n);
    forn(i,n)
		cin >> v[i];
	
	forsn(x,1,X+1)
		dp[0][x] = 0;
	dp[0][0] = 1;
	forsn(i, 1, n+1)
	forn(x, X+1)
	{
		int & ret = dp[i][x] = dp[i-1][x];
		if (v[i-1] <= x)
			ret = (ret + dp[i][x-v[i-1]]) % MOD;
	}
    
    cout << dp[n][X] << "\n";
    
    return 0;
}
