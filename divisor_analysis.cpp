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

template<tint M>
struct ModNum
{
    tint x;
    ModNum() { x=0; }
    explicit ModNum(tint xx) { x = xx; norm(); }
    void norm()
    {
        x = ((x%M)+M)%M;
    }
    ModNum operator+(const ModNum &o) const
    {
        return ModNum(x+o.x);
    }
    ModNum operator-(const ModNum &o) const
    {
        return ModNum(x-o.x);
    }
    ModNum operator*(const ModNum &o) const
    {
        return ModNum(x*o.x);
    }
};

struct Primo
{
    tint p, e;
};

template<tint M>
ModNum<M> potlog(ModNum<M> x, tint k)
{
    ModNum<M> ret(1);
    while (k != 0)
    {
        if (k%2) ret = ret * x;
        k /= 2;
        x = x*x;
    }
    return ret;
}

template<tint P>
ModNum<P> invMod(ModNum<P> x)
{
    assert(x.x != 0);
    // P es primo
    return potlog(x, P-2);
}

typedef ModNum<MOD> ModP;
typedef ModNum<MOD-1> ModPminus1;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<Primo> v(n);
    forn(i,n)
        cin >> v[i].p >> v[i].e;
    ModP cantidad(1);
    forn(i,n)
        cantidad = cantidad * ModP(v[i].e+1);
    vector<ModPminus1> prefixProd(n+1); // [0:i)
    prefixProd[0] = ModPminus1(1);
    forn(i,n)
        prefixProd[i+1] = prefixProd[i] * ModPminus1(v[i].e+1);
    vector<ModPminus1> suffixProd(n+1); // [i:n)
    suffixProd[n] = ModPminus1(1);
    dforn(i,n)
        suffixProd[i] = suffixProd[i+1] * ModPminus1(v[i].e+1);
    assert(prefixProd[n].x == suffixProd[0].x);
    ModP suma(1);
    forn(i,n)
    {
        ModP fact = potlog(ModP(v[i].p), v[i].e+1) - ModP(1);
        fact = fact * invMod(ModP(v[i].p-1));
        suma = suma * fact;
    }
    ModP producto(1);
    forn(i,n)
    {
        ModPminus1 expo = prefixProd[i] * suffixProd[i+1];
        expo = expo * ModPminus1((v[i].e * (v[i].e+1))/2);
        producto = producto * potlog(ModP(v[i].p), expo.x);
    }
    cout << cantidad.x << " " << suma.x << " " << producto.x << "\n";
    return 0;
}
