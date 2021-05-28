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

#define DBG(x) cerr << #x << " = " << (x) << endl

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MAXN = 2600;

struct Edge
{
    int node;
    tint cost;
};

tint bf[MAXN][MAXN]; // longitud, nodo
Edge bestParent[MAXN][MAXN]; // longitud, nodo

vector<Edge> parents[MAXN];

const tint INF = 1000000000000000000LL;

void printCycle(int node,int n)
{
    vector<Edge> path;
    forn(steps, n+1)
    {
        assert(node >= 0);
        Edge e = bestParent[n-steps][node];
        path.push_back({node, e.cost});
        node = e.node;
    }
    assert(node == -1);
    reverse(all(path));
    vector<bool> visited(n, false);
    stack<Edge> s;
    for (Edge e : path)
    {
        if (visited[e.node])
        {
            vector<int> cycle = {e.node};
            tint cycleCost = e.cost;
            assert(!s.empty());
            #define STACKTOP_NODE s.top().node
            while (STACKTOP_NODE != e.node)
            {
                cycle.push_back(STACKTOP_NODE);
                cycleCost += s.top().cost;
                visited[STACKTOP_NODE] = false;
                s.pop();
                assert(!s.empty());
            }
            cycle.push_back(e.node);
            if (cycleCost < 0)
            {
                dforn(i, cycle.size())
                {
                    if (i < int(cycle.size())-1)
                        cout << " ";
                    cout << 1+cycle[i];
                }
                cout << "\n";
            }
        }
        else
        {
            visited[e.node] = true;
            s.push(e);
        }
    }
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
        tint c;
        cin >> a >> b >> c;
        a--; b--;
        parents[b].push_back({a,c});
    }
     
    forn(i,n)
    {
        bf[0][i] = 0;
        bestParent[0][i] = {-1,0};
    }
    forsn(l,1,n+1)
    forn(i,n)
    {
        bf[l][i] = INF;
        bestParent[l][i] = {-1,INF};
        for (Edge edge : parents[i])
        {
            tint newCost = bf[l-1][edge.node] + edge.cost;
            if (newCost < bf[l][i])
            {
                bf[l][i] = newCost;
                bestParent[l][i] = edge;
            }
        }
    }
    forn(i,n)
    {
        tint bestCost = INF;
        forn(l,n)
            bestCost = min(bestCost, bf[l][i]);
        if (bf[n][i] < bestCost)
        {
            cout << "YES\n";
            printCycle(i,n);
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
