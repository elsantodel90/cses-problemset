#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

const tint INF_DIST = 1000000000000000000LL;
const int INF_EDGE_COUNT = 1000000000;

const int MAXN = 200000;

struct Edge { int dest, c; };
struct Item { int node; tint c; 
    bool operator>(const Item &o) const { return c > o.c; }
};

vector<Edge> g[MAXN];
tint dist[MAXN];

struct Data
{
    int nw, minE, maxE;
    bool isReady() const { return nw >= 0; }
} dataCache[MAXN];

const Data NOT_READY = {-1,-1,-1};
const Data EMPTY = {0,INF_EDGE_COUNT,-INF_EDGE_COUNT};

const int MOD = 1000000007;

Data data(int node)
{
    Data &ret = dataCache[node];
    if (!ret.isReady())
    {
        ret = EMPTY;
        for (Edge e : g[node])
        if (dist[node] + e.c == dist[e.dest])
        {
            Data destData = data(e.dest);
            ret.nw = (ret.nw+destData.nw)%MOD;
            ret.minE = min(ret.minE, 1+destData.minE);
            ret.maxE = max(ret.maxE, 1+destData.maxE);
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N,M;
    cin >> N >> M;
    forn(i,M)
    {
        int a,b,c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
    }
    const int SOURCE = 0;
    const int TARGET = N-1;
    forn(i,N)
        dist[i] = INF_DIST;
    priority_queue<Item, vector<Item>, greater<Item>> pq;
        
    pq.push({SOURCE, 0LL});
    dist[SOURCE] = 0;
    while (!pq.empty())
    {
        int node = pq.top().node; 
        tint nodeDist = pq.top().c;
        pq.pop();
        if (nodeDist != dist[node])
        {
            assert(nodeDist > dist[node]);
            continue;
        }
        for (Edge e : g[node])
        {
            tint nd = nodeDist + e.c;
            if (nd < dist[e.dest])
            {
                pq.push({e.dest, nd});
                dist[e.dest] = nd;
            }
        }
    }
    forn(i,N)
        dataCache[i] = NOT_READY;
    dataCache[TARGET] = {1, 0, 0};
    Data sourceData = data(SOURCE);
    cout << dist[TARGET] << " " << sourceData.nw << " " <<
            sourceData.minE << " " << sourceData.maxE << "\n";
    return 0;
}
