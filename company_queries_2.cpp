#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
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

typedef long long tint;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

namespace LCA
{
    // La cantidad maxima de vertices n debe ser menor que 2^(LVL-1).
    #define LVL 20
    #define MAXN (1<<LVL)
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
    int id, pp;

    void dfs(int x) {
        d[x] = id++;
        vec[0][pos[x] = pp++] = x;
        for (int y : t[x])
        if (d[y] == -1) {
            dfs(y);
            vec[0][pp++] = x;
        }
    }

    void lcaInit(int n,int raiz) {
        id = pp = 0;
        memset(d,-1,sizeof(d));
        dfs(raiz);
        mn_init(2*n-1);
    }

    int lca(int i,int j) {
        int a = pos[i], b = pos[j];
        if (a > b) swap(a,b);
        return mn(a,b+1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q;
    cin >> n >> q;
    forn(i,n-1)
    {
        int parent;
        cin >> parent;
        parent--;
        int child = i+1; 
        LCA::t[parent].push_back(child);
        LCA::t[child].push_back(parent);
    }
    LCA::lcaInit(n, 0);
    forn(i,q)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        cout << 1+LCA::lca(x,y) << "\n"; 
    }
    return 0;
}
