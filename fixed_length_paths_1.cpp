#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <cassert>
#include <map>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define all(c) (c).begin(), (c).end()

typedef long long tint;

const int MAXN = 250000;

vector<int> g[MAXN];

int nCentroid;

// centroid 0 a n-1
// tam es >= 1
// Devolver: tam o -centroid si lo encontre
int dfsCentroid(int node, int parent)
{
    int tam = 1;
    bool vaBien = true;
    for (int child : g[node])
    if (child != parent)
    {
        int retChild = dfsCentroid(child, node);
        if (retChild <= 0)
            return retChild;
        vaBien &= retChild <= nCentroid/2;
        tam += retChild;
    }
    vaBien &= nCentroid - tam <= nCentroid/2;
    return vaBien ? -node : tam;
}

int centroid(int n, int node)
{
    nCentroid = n;
    return -dfsCentroid(node, -1);
}

int k;

typedef vector<int> Histograma;

// cant de pares distintos que las alturas suman k
tint f(const Histograma &histograma)
{
    tint total = 0;
    forn(i, min(int(histograma.size()), k+1))
    {
        const int j = k-i;
        if (j >= int(histograma.size()))
            continue;
        if (i > j)
            break;
        if (i == j)
            total += (histograma[i] * tint(histograma[i]-1)) / 2;
        else
            total += histograma[i] * tint(histograma[j]);
    }
    return total;
}

void ensureSize(int tam, Histograma &histograma)
{
    if (int(histograma.size()) < tam)
        histograma.resize(max(tam, 2*int(histograma.size())), 0);
    //while (int(histograma.size()) < tam)
    //    histograma.push_back(0);
}

void sumar(Histograma &histogramaTotal, const Histograma &histogramaHijo)
{
    ensureSize(int(histogramaHijo.size()), histogramaTotal);
    forn(i, histogramaHijo.size())
        histogramaTotal[i] += histogramaHijo[i];
}

void dfsHistograma(int node, int parent, int h, Histograma &histograma)
{
    ensureSize(h+1, histograma);
    histograma[h]++;
    for (int y : g[node])
    if (y != parent)
        dfsHistograma(y, node, h+1, histograma);
}

tint solve(int n, int node)
{
    int x = centroid(n, node);
    
    tint total = 0;
    
    // Resolver para el problema con x como raiz
    // (cuantos caminos pasan por x)
    Histograma histogramaTotal = {1};
    for (int y : g[x])
    {
        Histograma histogramaHijo;
        dfsHistograma(y, x, 1, histogramaHijo);
        total -= f(histogramaHijo);
        sumar(histogramaTotal, histogramaHijo);
        int tamY = 0;
        for (int elem : histogramaHijo)
            tamY += elem;
        g[y].erase(find(all(g[y]), x));
        total += solve(tamY, y);
    }
    total += f(histogramaTotal);
    
    //for (int y : g[x])
    //{
    //    
    //    //for (int &elem : g[y])
    //    //if (elem == x)
    //    //{
    //    //    swap(g[y].back(), elem);
    //    //    g[y].pop_back();
    //    //    break;
    //    //}
    //}
    return total;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n >> k;
    
    forn(arista, n-1)
    {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    cout << solve(n, 0) << "\n";
    return 0;
}
