#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cassert>
 
using namespace std;
 
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
 
#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int MAXN = 100000;

vector<int> g[MAXN];
int _longest[MAXN];
int nextNode[MAXN];

int longest(int node)
{
    int &ret = _longest[node];
    if (ret == 0)
    {
        for (int y : g[node])
        {
            int ly = longest(y);
            if (ly > ret)
            {
                ret = ly;
                nextNode[node] = y;
            }
        }
        if (ret > 0)
            ret++;
        else
            ret = -1;
    }
    assert(ret != 0);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }
    _longest[n-1] = 1;
    int ret = longest(0);
    assert(ret != 0);
    if (ret < 0)
        cout << "IMPOSSIBLE\n";
    else
    {
        cout << ret << "\n1";
        int x = 0;
        while (x != n-1)
        {
            x = nextNode[x];
            cout << " " << x+1;
        }
        cout << "\n";
    }
    return 0;
}
