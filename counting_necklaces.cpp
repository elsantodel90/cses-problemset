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

using tint = long long;

const tint MOD = 1000000007;

tint gcd(tint a, tint b)
{
    if (a == 0)
        return b;
    else
        return gcd(b%a, a);
}

tint potlog(tint a, tint b)
{
    tint ret = 1;
    while (b > 0)
    {
        if (b%2 != 0) ret = (ret * a) % MOD;
        a = (a*a)%MOD;
        b /= 2;
    }
    return ret;
}

tint inverse(tint x)
{
    return potlog(x, MOD-2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    tint n,m;
    cin >> n >> m;
    tint ret = 0;
    forn(i,n)
        ret += potlog(m, gcd(i,n));
    cout << ((ret % MOD) * inverse(n)) % MOD << "\n";
    return 0;
}
