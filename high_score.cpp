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

const int MAXN = 4096;
const int MAXM = 8192;

tint distancia[MAXN];

struct Arista
{
	int a,b,x;
};

Arista aristas[MAXM];

const tint INF = 1000000000000000000LL;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	int n,m;
	cin >> n >> m;
	forn(i,m)
	{
		cin >> aristas[i].a >> aristas[i].b >> aristas[i].x;
		aristas[i].a--;
		aristas[i].b--;
	}
	forsn(i,1,n)
		distancia[i] = -INF;
	distancia[0] = 0;
	
	tint respuesta = -1;
	forn(veces, 2)
	{
		forn(paso, n)
		forn(i, m)
		{
			const Arista &eje = aristas[i];
			if (distancia[eje.a] == -INF)
				continue;
			tint nuevaDistancia = distancia[eje.a] + eje.x;
			if (nuevaDistancia > distancia[eje.b])
				distancia[eje.b] = (veces == 0) ? nuevaDistancia : INF;
		}
		if (veces == 0)
			respuesta = distancia[n-1];
		else if (distancia[n-1] > respuesta)
			respuesta = -1;
	}
	cout << respuesta << "\n";
	
    return 0;
}
