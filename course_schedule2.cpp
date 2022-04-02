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
int indeg[MAXN];

vector<int> orden;

void impossible()
{
    cout << "IMPOSSIBLE\n";
    exit(0);
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
        indeg[b]++;
        g[a].push_back(b);
    }
    
    vector<int> bolsa;
    bolsa.reserve(n);
    forn(i,n)
    if (indeg[i] == 0)
        bolsa.push_back(i);
    
    orden.reserve(n);
    
    while (!bolsa.empty())
    {
        int x = bolsa.back(); bolsa.pop_back();
        orden.push_back(x);
        for (int y : g[x])
        if (--indeg[y] == 0)
            bolsa.push_back(y);
    }
    
    if (int(orden.size()) < n)
        impossible();
        
    forn(i, n)
    {
        if (i > 0)
            cout << " ";
        cout << orden[i]+1;
    }
    cout << "\n";
    
    return 0;
}
