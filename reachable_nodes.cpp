#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,popcnt,abm,mmx,avx,tune=native")


#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

const int MAXN = 50000;

vector<int> g[MAXN];
bitset<MAXN> r[MAXN];

void go(int node)
{
    if (r[node].test(node))
        return;
    for (int y : g[node])
    {
        go(y);
        r[node] |= r[y];
    }
    r[node].set(node);
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
    forn(i,n)
        go(i);
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << r[i].count();
    }
    cout << "\n";
 
    return 0;
}
