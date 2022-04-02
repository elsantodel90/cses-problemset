#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <stack>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MAXN = 250000;
const int MAXEQ = 500000;

namespace Notebook
{

    int fch[2*MAXN], nch[2*MAXEQ], dst[2*MAXEQ], eqs; // Grafo
    void addeje(int s, int d) { nch[eqs]=fch[s]; dst[fch[s]=eqs++]=d; }
    void init() {
        memset(fch, 0xff, sizeof(fch));
        eqs=0;
    }
    int us[2*MAXN], lw[2*MAXN], id[2*MAXN];
    stack<int> q; int qv, cp;
    void tjn(int i) {
        lw[i] = us[i] = ++qv;
        id[i]=-2; q.push(i);
        for(int j = fch[i]; j!=-1; j=nch[j]) { int x = dst[j];
            if (!us[x] || id[x] == -2) {
                if (!us[x]) tjn(x);
                lw[i] = min(lw[i], lw[x]);
            }
        }
        if (lw[i] == us[i]) {
            int x; do { x = q.top(); q.pop(); id[x]=cp; } while (x!=i);
            cp++;
        }
    }
    void compFuertementeConexas(int n) { // Tarjan algorithm
        memset(us, 0, sizeof(us));
        memset(id, -1, sizeof(id));
        q=stack<int>(); qv = cp = 0;
        forn(i, n) {
            if (!us[i]) tjn(i);
        }
    }
};

tint monedas[MAXN];
tint compCoins[MAXN];
tint bestCoins[MAXN];

vector<int> g[MAXN];

tint f(int x)
{
    if (bestCoins[x] < 0)
    {
        bestCoins[x] = 0;
        for (int y : g[x])
            bestCoins[x] = max(bestCoins[x], f(y));
        bestCoins[x] += compCoins[x];
    }
    return bestCoins[x];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    forn(i,n)
        cin >> monedas[i];
    Notebook::init();
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        Notebook::addeje(a-1, b-1);
    }
    Notebook::compFuertementeConexas(n);
    forn(i,n)
    {
        int a = Notebook::id[i];
        for(int j = Notebook::fch[i]; j!=-1; j=Notebook::nch[j]) {
             int neighbor = Notebook::dst[j];
             int b = Notebook::id[neighbor];
             if (a != b)
                g[a].push_back(b);
        }
    }
    forn(i,n)
        compCoins[Notebook::id[i]] += monedas[i];
    int cantComponentes = Notebook::cp;
    forn(i,cantComponentes)
        bestCoins[i] = -1;
    tint best = 0;
    forn(i,cantComponentes)
        best = max(best, f(i));
    cout << best << "\n";
    return 0;
}
