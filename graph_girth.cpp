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


int bfs(int a, int b)
{
    queue<int> q;
    static int d[MAXN];
    forn(i,N)
        d[i] = INF;
    #define PUSH(x, dist) do {q.push(x); d[x] = dist;} while (false)
    PUSH(a, 0);
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        int nd = d[x]+1;
        for (int y : g[x])
        if ((x != a || y != b) && nd < d[y])
        {
            if (y == b)
                return 1 + nd;
            PUSH(y, nd);
        }
    }
    return INF;
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
    for (int b : g[a])
    if (a < b)
        ret = min(ret, bfs(a, b));
    
    if (ret == INF)
        ret = -1;
    cout << ret << "\n";
    
    return 0;
}
