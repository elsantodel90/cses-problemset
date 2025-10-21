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
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) cerr << #x << " = " << (x) << endl

#define SIZE(c) int((c).size())
#define ALL(c) begin(c),end(c)

typedef long long tint;

const int MAXN = 100000;

vector<int> revTopo;
vector<int> g[2][MAXN];
bool visited[2][MAXN];
int component[MAXN];
int currentComponent;

#define GO(k, x) if (!visited[k][x]) go(k, x)


void go(int k, int x)
{
    visited[k][x] = true;
    for (int y : g[k][x])
        GO(k, y);
    if (k == 0)
        revTopo.push_back(x);
    else
        component[x] = currentComponent;
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
        g[0][a].push_back(b);
        g[1][b].push_back(a);
    }

    forn(i,n)
        GO(0,i);
    currentComponent = 0;
    while (!revTopo.empty())
    {    
        int x = revTopo.back(); revTopo.pop_back();
        if (!visited[1][x])
        {
            currentComponent++;
            go(1, x);
        }
    }

    cout << currentComponent << "\n";
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << component[i];
    }
    cout << "\n";
    
    return 0;
}
