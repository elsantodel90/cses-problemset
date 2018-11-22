#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

const int MAXN = 1024;
const int MAX_X = 200000;

int h[MAXN], s[MAXN];
int dp[MAX_X];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,x;
    cin >> N >> x;
    forn(i,N)
        cin >> h[i];
    forn(i,N)
        cin >> s[i];
    forn(i,N)
    dforsn(j, h[i] , x+1)
        dp[j] = max(dp[j], dp[j-h[i]] + s[i]);
    cout << *max_element(dp, dp+x+1) << endl;
    return 0;
}
