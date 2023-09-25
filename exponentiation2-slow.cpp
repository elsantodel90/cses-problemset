#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

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

const tint P = 1000000007;

tint potlog(tint a, tint b, tint mod)
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
        tint r = potlog(b,c, P-1);
        return potlog(a,r, P);
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
