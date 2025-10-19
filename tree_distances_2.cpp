#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <queue>
#include <cassert>
#include <map>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define all(c) (c).begin(), (c).end()

//#define DBG(x) do {cerr << #x << " = " << (x) << endl; } while (false)
//#define RAYA do {cerr << " ================================= " << endl; } while (false)

typedef long long tint;

const int MAXN = 300000;

struct TamSum
{
    tint tam,sum;
    TamSum extend() const { return {tam+1, sum+tam};}
    TamSum combine(const TamSum &o) const { return {tam+o.tam-1, sum+o.sum};}
    TamSum remove(const TamSum &o) const { return {tam-o.tam+1, sum-o.sum};}
};

const TamSum SINGLE_NODE = {1, 0};


vector<int> g[MAXN];
TamSum altura[MAXN];
TamSum maxDist[MAXN];

void dfsAltura(int nodo, int parent)
{
    altura[nodo] = SINGLE_NODE;
    for (int y : g[nodo])
    if (y != parent)
    {
        dfsAltura(y, nodo);
        altura[nodo] = altura[y].extend().combine(altura[nodo]);
    }
}

void dfsMaxDist(int nodo, int parent, TamSum bestCuenta)
{
    maxDist[nodo] = altura[nodo].combine(bestCuenta);
    
    for (int y : g[nodo])
    if (y != parent)
    {
        // excluyendo el camino hacia el hijo!!!!!
        dfsMaxDist(y, nodo, maxDist[nodo].remove(altura[y].extend()).extend());
    }
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    forn(i,n-1)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfsAltura(0,-1);
    dfsMaxDist(0,-1,SINGLE_NODE);
    
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << maxDist[i].sum;
    }
    cout << "\n";
    
    return 0;
}
