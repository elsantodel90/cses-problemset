#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>
#include <cassert>
#include <vector>
#include <list>

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
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int MAXN = 100100;

vector<int> ancestors;
vector<int> g[MAXN];
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;
int color[MAXN];

void dfs(int x)
{
    color[x] = GRAY;
    ancestors.push_back(x);
    for (int y : g[x])
    if (color[y] == WHITE)
        dfs(y);
    else if (color[y] == GRAY)
    {
        vector<int> ret = {y};
        while (ancestors.back() != y)
        {
            ret.push_back(ancestors.back());
            ancestors.pop_back();
        }
        ret.push_back(y);
        cout << SIZE(ret) << "\n";
        forn(i, SIZE(ret))
        {
            if (i > 0)
                cout << " ";
            cout << ret[i]+1;
        }
        cout << "\n";
        exit(0);
    }
    ancestors.pop_back();
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
        int x,y;
        cin >> x >> y;
        x--; y--;
        g[y].push_back(x);
    }
    forn(i,n)
    if (color[i] == WHITE)
        dfs(i);
    cout << "IMPOSSIBLE\n";
    return 0;
}
