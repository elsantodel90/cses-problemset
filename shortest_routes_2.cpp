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

typedef long long tint;

const tint INF = 1000000000000000LL;

const int MAXN = 512;

tint dist[MAXN][MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m,q;
    cin >> n >> m >> q;
    forn(i,n)
    forn(j,n)
        dist[i][j] = INF;
    forn(i,n)
        dist[i][i] = 0;
    forn(i,m)
    {
        int x,y;
        tint c;
        cin >> x >> y >> c;
        x--; y--;
        dist[x][y] = min(dist[x][y], c);
        dist[y][x] = min(dist[y][x], c);
    }
    
    forn(k,n)
    forn(i,n)
    forn(j,n)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        
    forn(i,q)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        tint ret = dist[a][b];
        if (ret == INF)
            ret = -1;
        cout << ret << "\n";;
    }
    
    return 0;
}
