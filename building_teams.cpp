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

const int MAXN = 100000;

vector<int> g[MAXN];
int color[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    forn(i,m)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> q;
    forn(i,n)
    if (color[i] == 0)
    {
        color[i] = 1;
        q.push_back(i);
        while (!q.empty())
        {
            int x = q.back(); q.pop_back();
            for (int y : g[x])
            if (color[y] == 0)
            {
                color[y] = 3 - color[x];
                q.push_back(y);
            }
            else if (color[y] == color[x])
            {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << color[i];
    }
    cout << "\n";
    return 0;
}
