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

#define SIZE(c) int((c).size())
#define ALL(c) begin(c),end(c)

typedef long long tint;

const int MAXN = 8192;

struct Edge
{
    int node;
    tint diff;
};

vector<Edge> g[MAXN];
tint P[MAXN];
bool visited[MAXN];

void dfs(int node)
{
    visited[node] = true;
    for (Edge edge : g[node])
    {
        int neighbor = edge.node;
        tint expectedValue = P[node] + edge.diff;
        if (!visited[neighbor])
        {
            P[neighbor] = expectedValue;
            dfs(neighbor);
        }
        else if (P[neighbor] != expectedValue)
        {
            cout << "NO\n";
            exit(0);
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
        a--;
        g[a].push_back({b, c});
        g[b].push_back({a, -c});
    }
    forn(i,n+1)
    if (!visited[i])
    {
        P[i] = 0;
        dfs(i);
    }
    cout << "YES\n";
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << P[i+1] - P[i];
    }
    cout << "\n";
    return 0;
}
