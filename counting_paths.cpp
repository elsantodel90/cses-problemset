#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=(n)-1;i>=(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int MAXN = 250000;
vector<int> g[MAXN];
vector<int> queries[MAXN];

int ret[MAXN];
int finalDelta[MAXN];

int p[MAXN];

void dsuInit(int n)
{
    forn(i,n)
        p[i] = i;
}

int root(int x)
{
    if (p[x] == x)
        return x;
    else
        return p[x] = root(p[x]);
}

// hang a into b
void join(int a, int b)
{
    int ra = root(a);
    int rb = root(b);
    p[ra] = rb;
}

bool visited[MAXN];

void dfs(int node, int parent)
{
    visited[node] = true;
    for (int other : queries[node])
    {
        assert(other != node);
        if (visited[other])
        {
            ret[root(other)] -= 2;
            finalDelta[root(other)]++;
        }
    }
    for (int child : g[node])
    if (child != parent)
    {
        dfs(child, node);
        ret[node] += ret[child];
        join(child, node);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;

    dsuInit(n);

    forn(k,2)
    forn(i,k==0 ? n-1 : m)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        if (k == 1 && x == y)
        {
            finalDelta[x]++;
        }
        else
        {
            (k==0?g:queries)[x].push_back(y);
            (k==0?g:queries)[y].push_back(x);
            ret[x] += k==1;
            ret[y] += k==1;
        }
    }
    dfs(0, -1);
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << ret[i] + finalDelta[i];
    }
    cout << "\n";
    return 0;
}
