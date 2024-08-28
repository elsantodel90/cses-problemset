#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <cassert>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

const tint INF = 1000000000000000000LL;

struct Edge
{
    int dest, cost;
};

const int MAXN = 200000;
tint dist[2][MAXN];
vector<Edge> g[MAXN];

struct Item
{
    int canHalve, node;
    tint cost;
    
    bool operator<(const Item &o) const { return cost > o.cost; }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n >> m;
    forn(i,m)
    {
        int node;
        Edge e;
        cin >> node >> e.dest >> e.cost;
        node--; e.dest--; 
        g[node].push_back(e);
    }
    
    forn(canHalve, 2)
    forn(i,n)
        dist[canHalve][i] = INF;
    priority_queue<Item> pq;
    #define PUSH_ITEM(canHalve, node, d) do { dist[canHalve][node] = (d); pq.push({canHalve, (node), (d)}); } while (false)
    PUSH_ITEM(true, 0, 0);
    while (!pq.empty())
    {
        Item item = pq.top(); pq.pop();
        if (item.cost > dist[item.canHalve][item.node])
            continue;
        for (const Edge &e : g[item.node])
        forn(canHalve, item.canHalve+1)
        {
            int edgeCost = (item.canHalve && !canHalve) ? e.cost/2 : e.cost;
            tint nd = item.cost + edgeCost;
            if (nd < dist[canHalve][e.dest])
                PUSH_ITEM(canHalve, e.dest, nd);
        }
    }
    cout << min(dist[false][n-1], dist[true][n-1]) << "\n";
    
    return 0;
}
