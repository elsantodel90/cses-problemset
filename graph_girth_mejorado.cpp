#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

const int MAXN = 3000;
int N;

vector<int> g[MAXN];

const int INF = 1000000000;


int bfs(int a)
{
    queue<int> q;
    static int d[MAXN];
    static int p[MAXN];
    forn(i,N)
        d[i] = INF;
    #define PUSH(x, dist, par) do {q.push(x); d[x] = dist; p[x] = par;} while (false)
    PUSH(a, 0, -1);
    int ret = INF;
    int maxCapa = INF;
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        if (d[x] > maxCapa)
            return ret;
        int nd = d[x]+1;
        for (int y : g[x])
        if (nd < d[y])
            PUSH(y, nd, x);
        else if (y != p[x])
        {
            // Encontre ciclo!
            // MAL!!! (ES APROXIMADO) return d[x] + d[y] + 1;
            ret = min(ret, d[x] + d[y] + 1);
            if (ret % 2 != 0)
                return ret;
            else
                maxCapa = d[x];
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M;
    cin >> N >> M;
    forn(i,M)
    {
        int a,b;
        cin >> a >> b;
        a--;b--;
        assert(a != b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    int ret = INF;
    forn(a,N)
        ret = min(ret, bfs(a));
    
    if (ret == INF)
        ret = -1;
    cout << ret << "\n";
    
    return 0;
}
