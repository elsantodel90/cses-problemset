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

int centroid(int n)
{
    nCentroid = n;
    return -dfsCentroid(0, -1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    forn(arista, n-1)
    {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cout << centroid(n) + 1 << endl;
    return 0;
}
