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

const int MAXN = 110000;

vector<int> g[MAXN];

vector<int> orden;

int color[MAXN];

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

void impossible()
{
    cout << "IMPOSSIBLE\n";
    exit(0);
}

void dfs(int x)
{
    color[x] = GRAY;
    
    for (int y : g[x])
    if (color[y] == GRAY)
        impossible();
    else if (color[y] == WHITE)
        dfs(y);
    
    orden.push_back(x);
    color[x] = BLACK;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }
    
    orden.reserve(n);
    
    forn(i,n)
    if (color[i] == WHITE)
        dfs(i);
    
    reverse(all(orden));
    
    forn(i, n)
    {
        if (i > 0)
            cout << " ";
        cout << orden[i]+1;
    }
    cout << "\n";
    
    return 0;
}
