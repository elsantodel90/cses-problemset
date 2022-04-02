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

namespace LCA
{
    // La cantidad maxima de vertices n debe ser menor que 2^(LVL-1).
    const int LVL = 20;
    const int MAXN = (1<<LVL);
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

    vector<int> t[MAXN]; // Tree
    int pos[MAXN];
    int pp;

    void dfs(int x, int depth) {
        d[x] = depth;
        vec[0][pos[x] = pp++] = x;
        for (int y : t[x])
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
        return d[i] + d[j] - 2 * d[lca(i,j)];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,q;
    cin >> n >> q;
    forn(i,n-1)
    {
        int a,b;
        cin >> a >> b;
        LCA::t[a-1].push_back(b-1);
        LCA::t[b-1].push_back(a-1);
    }
    LCA::lcaInit(n,0);
    forn(i,q)
    {
        int a,b;
        cin >> a >> b;
        cout << LCA::dist(a-1, b-1) << "\n";
    }
    
    return 0;
}
