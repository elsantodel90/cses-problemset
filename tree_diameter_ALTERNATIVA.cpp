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
	int distancia, maxCaminoRaiz;
};

ResultadoDfs dfs(int nodo, int parent)
{
	ResultadoDfs ret;
	ret.distancia = 0;
	int best1 = 0, best2 = 0; // best1 > best2
	for (int y : g[nodo])
	if (y != parent)
	{
		ResultadoDfs childResult = dfs(y, nodo);
		ret.distancia = max(ret.distancia, childResult.distancia);
		childResult.maxCaminoRaiz++;
		if (childResult.maxCaminoRaiz > best1)
		{
			best2 = best1;
			best1 = childResult.maxCaminoRaiz;
		}
		else if (childResult.maxCaminoRaiz > best2)
			best2 = childResult.maxCaminoRaiz;
	}
	ret.maxCaminoRaiz = best1;
	ret.distancia = max(ret.distancia, best1 + best2);
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
    
    cout << dfs(0,-1).distancia << "\n";
    
    return 0;
}
