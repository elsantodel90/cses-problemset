#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <queue>
#include <cassert>
#include <map>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define all(c) (c).begin(), (c).end()

typedef long long tint;

const int MAXN = 300000;

vector<int> g[MAXN];

struct ResultadoDfs
{
	int distancia, nodo;
};

ResultadoDfs dfs(int nodo, int parent)
{
	ResultadoDfs ret;
	ret.nodo = nodo;
	ret.distancia = 0;
	for (int y : g[nodo])
	if (y != parent)
	{
		ResultadoDfs childResult = dfs(y, nodo);
		childResult.distancia++;
		if (childResult.distancia > ret.distancia)
			ret = childResult;
	}
	return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    forn(i,n-1)
	{
		int a,b;
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
    
    cout << dfs(dfs(0,-1).nodo,-1).distancia << "\n";
    
    return 0;
}
