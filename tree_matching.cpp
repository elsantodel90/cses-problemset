#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

const int MAXN = 210000;

vector<int> g[MAXN];

int ret;

bool dfs(int node, int parent)
{
    bool available = false;
    for (int child : g[node])
    if (child != parent)
        available |= dfs(child, node);
    ret += available;
    return !available;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    forn(i,n-1)
    {
        int a,b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ret = 0;
    dfs(0, -1);
    cout << ret << "\n";
    return 0;
}
