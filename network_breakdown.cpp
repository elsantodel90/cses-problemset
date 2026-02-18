#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=(n)-1;i>=(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int MAXN = 110'000;
int p[MAXN];
int componentCount;

void initUF(int n)
{
    forn(i,n)
        p[i] = i;
    componentCount = n;
}

int root(int x)
{
    if (x == p[x])
        return x;
    else
        return p[x] = root(p[x]);
}

void join(int a, int b)
{
    int ra = root(a);
    int rb = root(b);
    p[ra] = rb;
    componentCount -= ra != rb;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k;
    cin >> n >> m >> k;
    initUF(n);
    set<pair<int,int>> edges;
    forn(i,m)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        edges.insert(minmax(x,y));
    }
    vector<pair<int,int>> joins(k);
    forn(i,k)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        joins[k-1-i] = minmax(x,y);
        edges.erase(joins[k-1-i]);
    }
    for (auto e : edges)
        join(e.first, e.second);
    vector<int> ret(k);
    forn(i,k)
    {
        ret[k-1-i] = componentCount;
        join(joins[i].first, joins[i].second);
    }
    forn(i,k)
    {
        if (i > 0)
            cout << " ";
        cout << ret[i];
    }
    cout << "\n";
    return 0;
}
