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

const tint MOD = 1000000007;

inline tint potlog(tint a, tint b)
{
    tint ret = 1;
    while (b > 0)
    {
        if (b % 2) ret = (ret*a) % MOD;
        a = (a*a)%MOD;
        b /= 2;
    }
    return ret;
}

inline tint inverse(tint x)
{
    return potlog(x, MOD-2);
} 

const int MAXN = 1000000;

int factorial[MAXN+1];

inline tint binom(int n, int k)
{
    return (((factorial[n] * inverse(factorial[k]))%MOD) * inverse(factorial[n-k])) % MOD;
} 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    factorial[0] = 1;
    forn(i,MAXN)
        factorial[i+1] = int((factorial[i] * tint(i+1)) % MOD);
    
    int n,k;
    cin >> n >> k;
    tint ret = 0;
    forn(i,k)
    {
        tint coef = (k+i)%2 == 0 ? -k : k;
        coef = (coef * binom(k-1, i)) % MOD;
        ret += (coef * potlog(i+1, n-1))%MOD;
    }
    cout << (((ret%MOD)+MOD)%MOD) << "\n";
    
    return 0;
}
