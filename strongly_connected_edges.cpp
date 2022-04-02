#include <iostream>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <cassert>
#include <vector>

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
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef vector<int> vint;
typedef pair<tint,tint> ptint;

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

template <typename T>
istream & operator >>(istream &is, vector<T>& v) {
    int n;
    is >> n;
    v.resize(n);
    forn(i,n)
        is >> v[i];
    return is;
}

const int MAXN = 110000;

vector<int> g[MAXN];
vector<int> gOutput[MAXN];

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

int visited[MAXN];

void dfs(int node, int parent)
{
    visited[node] = GRAY;
    for (int neighbor : g[node])
    if (neighbor != parent)
    {
        if (visited[neighbor] != BLACK)
            gOutput[node].push_back(neighbor);
        if (visited[neighbor] == WHITE)
            dfs(neighbor, node);
    }
    visited[node] = BLACK;
}

int n;

void clean(vector<int> graph[])
{
    forn(i,n) graph[i].clear();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    cin >> n >> m;
    
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    dfs(0,-1);
    forn(i,n) visited[i] = WHITE;
    clean(g);
    forn(i,n)
    for (int j : gOutput[i])
        g[j].push_back(i);
    
    clean(gOutput);
    dfs(0,-1);
    forn(i,n)
    if (visited[i] != BLACK)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    
    forn(i,n)
    for (int j : g[i])
        cout << j+1 << " " << i+1 << "\n";
    return 0;
}
