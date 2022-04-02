#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

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
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
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

struct Poly
{
    tint a,b; // aX + b
    Poly operator *(const Poly &o) const
    {
        tint a1a2 = (a * o.a)%MOD;
        tint nA = (a1a2 + (a * o.b)%MOD + (b * o.a)%MOD) % MOD;
        tint nB = (a1a2 + (b * o.b)%MOD) % MOD;
        return {nA, nB};
    }
};

Poly potLog(Poly a, tint n)
{
    Poly res = {0, 1};
    // Invariante: rta = a^n * res
    while (n > 0)
    {
        if (n % 2) res = res * a;
        a = a*a;
        n /= 2;
    }
    return res;
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    tint index;
    cin >> index;

    Poly p = potLog({1, 0}, index);
    
    cout << p.a << "\n";
    
    return 0;
}
