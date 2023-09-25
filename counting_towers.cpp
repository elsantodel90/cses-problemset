#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>

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
#define ALL(c) (c).begin(), (c).end()
#define esta(x,c) ((c).find(x) != (c).end())

typedef long long tint;
typedef pair<int,int> pint;
typedef vector<int> vint;
typedef pair<tint,tint> ptint;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

template <typename T>
istream & operator >>(istream &is, vector<T>& v) {
    int n;
    is >> n;
    v.resize(n);
    forn(i,n)
        is >> v[i];
    return is;
}

const tint MOD = 1000000007;

const int MAXN = 1001000;

int f[MAXN], g[MAXN];
int pot2[2*MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pot2[0] = 1;
    forn(i, 2*MAXN-1)
        pot2[i+1] = (pot2[i] * 2) % MOD;

    f[0] = g[0] = 1;
    int sumOfF = f[0];
    forsn(n, 1, MAXN)
    {
        g[n] = sumOfF;
        f[n] = int((((4LL * f[n-1] - 3LL * g[n-1] + g[n]) % MOD)+MOD)%MOD);
        sumOfF += f[n];
        sumOfF %= MOD;
    }

    int TT;
    cin >> TT;
    forn(tt,TT)
    {
        int n;
        cin >> n;
        cout << f[n] << "\n";
    }
    
    return 0;
}
