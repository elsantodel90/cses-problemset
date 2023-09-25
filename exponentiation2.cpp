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

using tint = long long;

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

const tint P = 1000000007;

template <tint mod>
tint potlog(tint a, tint b)
{
    tint ret = 1;
    while (b > 0) // (ret * a^b) % mod es la respuesta buscada
    {
        if (b % 2 != 0) ret = (ret * a) % mod;
        b /= 2;
        a = (a*a)%mod;
    }
    return ret % mod;
}

tint calcpot(tint a,tint b,tint c)
{
    if (a == 0)
    {
        if (b == 0 && c > 0) // b^c == 0
            return 1;
        else
            return 0;
    }
    else
    {
        tint r = potlog<P-1>(b,c);
        return potlog<P>(a,r);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    forn(i,N)
    {
        tint a,b,c;
        cin >> a >> b >> c;
        cout << calcpot(a,b,c) << "\n";
    }

    return 0;
}
