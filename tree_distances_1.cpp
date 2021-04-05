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

#define DBG(x) do {} while (false)
#define RAYA do {} while (false)

typedef long long tint;

const int MAXN = 300000;

vector<int> g[MAXN];
int altura[MAXN];
int maxDist[MAXN];

void dfsAltura(int nodo, int parent)
{
    altura[nodo] = 0;
    for (int y : g[nodo])
    if (y != parent)
    {
        dfsAltura(y, nodo);
        altura[nodo] = max(altura[nodo], 1 + altura[y]);
    }
}

// bestCuenta es el maximo valor de -profAncestro + maxAltura[excluyendo el camino hacia el hijo] 
void dfsMaxDist(int nodo, int parent, int bestCuenta, int prof)
{
    DBG(nodo);
    DBG(prof);
    DBG(bestCuenta);
    DBG(parent);
    RAYA;
    maxDist[nodo] = max(altura[nodo], prof + bestCuenta);
    // Falta calcular hacia arriba
    int best1 = 0, best2 = 0; // best1 > best2
    int best1Index = -1; // best1 > best2
    for (int y : g[nodo])
    if (y != parent)
    {
        int maxAlturaChild = 1 + altura[y];
        if (maxAlturaChild > best1)
        {
            best2 = best1;
            best1 = maxAlturaChild;
            best1Index = y;
        }
        else if (maxAlturaChild > best2)
            best2 = maxAlturaChild;
    }
    
    
    for (int y : g[nodo])
    if (y != parent)
    {
        // excluyendo el camino hacia el hijo!!!!!
        int maxAlturaChild = (y == best1Index) ? best2 : best1;
        int cuenta = -prof + maxAlturaChild;
        dfsMaxDist(y, nodo, max(cuenta, bestCuenta) , prof + 1);
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
    dfsMaxDist(0,-1,0,0);
    
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << maxDist[i];
    }
    cout << "\n";
    
    return 0;
}
