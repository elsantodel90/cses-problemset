#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

using tint = long long;

const int MAXN = 210000;

tint dp[MAXN];

struct Interval
{
    int a,b,w;
    bool operator<(const Interval &o) const
    {
        return a < o.a;
    }
};

Interval inter[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    forn(i,n)
    {
        cin >> inter[i].a >> inter[i].b >> inter[i].w;
        inter[i].b++;
    }
    sort(inter, inter+n);
    dforn(i,n)
    {
        int j = int(lower_bound(inter+i+1, inter+n, (Interval){inter[i].b,0,0}) - inter);
        dp[i] = max(dp[i+1], inter[i].w + dp[j]);
    }
    cout << dp[0] << "\n";
    return 0;
}
