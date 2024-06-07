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

const int MOD = 1000000007;

const int MAXN = 100100;

int parent[MAXN];

int root(int x)
{
    if (parent[x] == x)
        return x;
    else
        return parent[x] = root(parent[x]);
}

void join(int a,int b)
{
    parent[root(a)] = root(b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    forn(i,n)
        parent[i] = i;
    forn(i,m)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        join(x,y);
    }
    int c = 0;
    forn(i,n)
        c += parent[i] == i;
    int ret = 1;
    forn(i, m-n+c)
        ret = (ret*2) % MOD;
    cout << ret << "\n";
    return 0;
}
