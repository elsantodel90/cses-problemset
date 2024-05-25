#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define qforsn(i,s,n) for(i=int(s);i<int(n);i++)
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

template<typename T>
using MinPQ = priority_queue<T, vector<T>, greater<T>>;
using tint = long long;


template<typename T>
void forn(int n, const T &codigo)
{
    for (int i = 0; i < n; i++)
        codigo(i);
}


template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    cout << "[";
    forn(v.size(), [&](int &i)
    {
        if (i > 0) os << " ";
        os << v[i];
    });
    cout << "]";
    return os;
}

const int MAXN = 110000;

struct Edge
{
    int node;
    tint length;
};

const tint INF = 1000000000000000000;

vector<Edge> g[MAXN];
int n;

struct Item
{
    int node;
    tint dist;
    
    bool operator<(const Item &other) const
    {
        return dist < other.dist;
    }
    
    bool operator>(const Item &other) const
    {
        return other < *this;
    }
};

vector<tint> dijkstra(int start)
{
    vector<tint> dist(n, INF);
    MinPQ<Item> pq;
    #define IMPROVE(node, d) do {dist[node] = (d); pq.push({node, (d)});} while (false)
    IMPROVE(start, 0);
    while (!pq.empty())
    {
        Item item = pq.top(); pq.pop();
        int x = item.node;
        if (item.dist != dist[x])
            continue;
        for (Edge e : g[x])
        {
            // x --> y
            int y = e.node;
            tint newDist = item.dist + e.length;
            if (newDist < dist[y])
                IMPROVE(y, newDist);
        }
    }
    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    cin >> n >> m;
    
    forn(m, [&](int&)
    {
        int a,b;
        tint c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
    });
    
    vector<tint> ret = dijkstra(0);
    forn(SIZE(ret), [&](int &i)
    {
        if (i > 0)
            cout << " ";
        cout << ret[i];
    });
    cout << "\n";
    
    return 0;
}
