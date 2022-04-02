#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) cerr << #x << " = " << (x) << endl

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MAXN = 110000;

const tint INF = 1000000000000000000LL;

struct Edge
{
    int neighbor;
    tint cost;
};

const int MAXK = 16;

vector<Edge> g[MAXN];
int nextDist[MAXN];
tint d[MAXN][MAXK];

struct Item
{
    int node,next;
    tint dist;
    bool operator<(const Item &o) const
    {
        return dist > o.dist || 
        (dist == o.dist && node < o.node);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m,k;
    cin >> n >> m >> k;
    
    forn(i,m)
    {
        int a,b;
        tint c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b,c});
    }

    forn(i,n)
    forn(j,k+1)
        d[i][j] = INF;

    priority_queue<Item> pq;
    pq.push({0,0,0});
    d[0][0] = 0;
    
    while (!pq.empty())
    {
        int node = pq.top().node;
        tint currentDist = pq.top().dist;
        int itemK = pq.top().next;
        pq.pop();
        if (itemK < nextDist[node])
            continue;
        
        if (++nextDist[node] < k)
            pq.push({node, nextDist[node], d[node][nextDist[node]]});
        
        for (Edge e : g[node])
        {
            int y = e.neighbor;
            if (nextDist[y] < k)
            {
                tint newDist = currentDist + e.cost;
                bool mustPush = newDist < d[y][nextDist[y]]; 
                forsn(j,nextDist[y], k)
                if (d[y][j] > newDist)
                {
                    dforsn(j2, j+1, k)
                        d[y][j2] = d[y][j2-1];
                    d[y][j] = newDist;
                    break;
                }
                if (mustPush)
                    pq.push({y, nextDist[y], d[y][nextDist[y]]});
            }
        }
    }
    
    forn(i, k)
    {
        if (i > 0)
            cout << " ";
        cout << d[n-1][i];
    }
    cout << "\n";
    
    return 0;
}
