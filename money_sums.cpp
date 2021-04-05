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

const int MAX_N = 128;
const int MAX_X = 110000;

bool dp[MAX_N][MAX_X];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> v(n);
    forn(i,n)
		cin >> v[i];
	
	forsn(x,1,MAX_X)
		dp[0][x] = false;
	dp[0][0] = true;
	forsn(i, 1, n+1)
	forn(x, MAX_X)
	{
		bool & ret = dp[i][x] = dp[i-1][x];
		if (v[i-1] <= x)
			ret |= dp[i-1][x-v[i-1]];
	}
    int outputSize = 0;
    forsn(x,1, MAX_X)
		outputSize += dp[n][x];
		
		
    cout << outputSize << "\n";
    
    bool pri = true;
    forsn(x,1, MAX_X)
    if (dp[n][x])
    {
		if (pri)
			pri = false;
		else
			cout << " ";
		cout << x;
	}
    cout << "\n";
    return 0;
}
