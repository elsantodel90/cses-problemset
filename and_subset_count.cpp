#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=(n)-1;i>=(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int BITS = 18;
int v[1<<BITS];
int pot2[(1<<BITS)+1];
const int MOD = 1'000'000'007;



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pot2[0] = 1;
    forn(i, (1<<BITS))
        pot2[i+1] = (2*pot2[i])%MOD;
    
    int n;
    cin >> n;
    forn(i,n)
    {
        int x;
        cin >> x;
        v[x]++;
    }
    
    forn(veces, 2)
    {
        forn(bit,BITS)
        forn(lowmask, 1<<bit)
        for(int highmask = 0; highmask < (1<<BITS); highmask += 1<<(bit+1))
        {
            int mask = lowmask | highmask;
            // La primera vuelta no es modular,
            // pero los numeros son chicos asi que no importa
            v[mask] = (v[mask] + v[mask|(1<<bit)]) % MOD;
        }
        forn(mask,1<<BITS)
        {
            if (veces == 0)
                v[mask] = pot2[v[mask]];
            if (__builtin_popcount(mask) % 2 != 0)
                v[mask] = -v[mask];
        }
    }
    forn(i,n+1)
    {
        if (i > 0)
            cout << " ";
        cout << (v[i]%MOD+MOD)%MOD;
    }
    cout << "\n";
    return 0;
}
