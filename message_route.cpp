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

const int MAXN = 100000;

vector<int> g[MAXN];
int parent[MAXN];
int dist[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    forn(i,m)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    queue<int> q;
    q.push(n-1);
    dist[n-1] = 0;
    parent[n-1] = n-1;
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        for (int y : g[x])
        if (parent[y] == 0)
        {
            parent[y] = x;
            dist[y] = dist[x]+1;
            q.push(y);
        }
    }
    if (parent[0] == 0)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    cout << dist[0] + 1 << "\n1";
    int x = 0;
    forn(i,dist[0])
    {
        x = parent[x];
        cout << " " << x+1;
    }
    cout << "\n";
    return 0;
}
