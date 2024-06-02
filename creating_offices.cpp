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

// La cantidad maxima de vertices n debe ser menor que 2^(LVL-1).
const int LVL = 20;
const int MAXN = 1<<LVL;

vector<int> t[MAXN]; // Tree

namespace LCA
{
    int d[MAXN];

    bool fcmp(int a,int b) { return d[a] < d[b];}

    int vec[LVL][MAXN];
    int mn(int i, int j) { // intervalo [i,j)
        int p = 31-__builtin_clz(j-i);
        return min(vec[p][i],vec[p][j-(1<<p)],fcmp);
    }
    void mn_init(int n) {
        int mp = 31-__builtin_clz(n);
        forn(p, mp) forn(x, n-(1<<p)) vec[p+1][x] = min(vec[p][x], vec[p][x+(1<<p)],fcmp);
    }

    int pos[MAXN];
    int pp;

    void dfs(int x, int depth) {
        d[x] = depth;
        vec[0][pos[x] = pp++] = x;
        for(int y : t[x])
        if (d[y] == -1) {
            dfs(y, depth+1);
            vec[0][pp++] = x;
        }
    }

    void lcaInit(int n,int raiz) {
        pp = 0;
        memset(d,-1,sizeof(d));
        dfs(raiz, 0);
        mn_init(2*n-1);
    }

    int lca(int i,int j) {
        int a = pos[i], b = pos[j];
        if (a > b) swap(a,b);
        return mn(a,b+1);
    }
    
    int dist(int i, int j)
    {
        return d[i] + d[j] - 2 * d[lca(i, j)];
    }
};

const int MAX_PENDING_SIZE = 350;

bool dead[MAXN];
vector<int> pending;
int d;

bool okMinDist(int node)
{
    for (int x : pending)
        if (LCA::dist(x, node) < d)
            return false;
    return true;
}

int bfsDist[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n >> d;
    forn(i,n-1)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        t[a].push_back(b);
        t[b].push_back(a);
    }
    LCA::lcaInit(n, 0);
    vector<int> nodes(n);
    forn(i,n)
        nodes[i] = i;
    sort(rbegin(nodes), rend(nodes), LCA::fcmp);
    vector<int> ret;
            
    for (int node : nodes)
    {
        if (SIZE(pending) > MAX_PENDING_SIZE)
        {
            forn(i,n)
                bfsDist[i] = n+1;
            #define BFS_PUSH(node, dist) do  {bfsDist[node] = dist; q.push(node); } while (false)
            queue<int> q;
            for (int x : pending)
                BFS_PUSH(x, 0);
            pending.clear();
            while (!q.empty())
            {
                int x = q.front(); q.pop();
                if (bfsDist[x] < d)
                    dead[x] = true;
                else
                    break;
                int newDist = bfsDist[x] + 1;
                for (int y : t[x])
                if (newDist < bfsDist[y])
                    BFS_PUSH(y, newDist);
            }
        }
        if (!dead[node] && okMinDist(node))
        {
            ret.push_back(node);
            pending.push_back(node);
        }
    }
    cout << SIZE(ret) << "\n";
    forn(i, SIZE(ret))
    {
        if (i > 0)
            cout << " ";
        cout << ret[i]+1;
    }
    cout << "\n";
    return 0;
}



