#include <iostream>
#include <algorithm>
#include <vector>
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
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

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

struct pto
{
    tint x,y;
    pto operator+(const pto &o) const { return {x+o.x, y+o.y}; }
    pto operator-(const pto &o) const { return {x-o.x, y-o.y}; }
    tint operator*(const pto &o) const { return x*o.x + y*o.y; }
    tint operator^(const pto &o) const { return x*o.y - y*o.x; }
};

istream &operator >>(istream &is, pto &p)
{
    return is >> p.x >> p.y;
}

int signo(tint x)
{
    return (x>0) - (x<0);
}

bool alineados(pto a,pto b, pto c)
{
    return ((b-a)^(c-a)) == 0;
}

bool estaEnSegmento(pto p, pto A, pto B)
{
    return alineados(p,A,B) && ((p-A)*(p-B)) <= 0;
}

bool estaEnFrontera(pto p, const vector<pto> &polygon)
{
    const int n = SIZE(polygon);
    forn(i, n)
    if (estaEnSegmento(p, polygon[i], polygon[(i+1)%n]))
        return true;
    return false;
}

bool estaAdentro(pto p, const vector<pto> & polygon)
{
    bool ret = false;
    const int n = SIZE(polygon);
    forn(i, n)
    {
        const pto A = polygon[i];
        const pto B = polygon[(i+1)%n];
        #define ARRIBA(punto) ((punto).y >= p.y)
        if (ARRIBA(A) != ARRIBA(B))
        {
            int signo1 = signo((A-p)^(B-A));
            int signo2 = signo(pto({1,0}) ^(B-A));
            assert(signo1 != 0);
            assert(signo2 != 0);
            if (signo1 * signo2 > 0)
                ret = !ret;
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<pto> polygon(n);
    forn(i,n)
        cin >> polygon[i];
    forn(i,m)
    {
        pto p;
        cin >> p;
        if (estaEnFrontera(p, polygon))
            cout << "BOUNDARY\n";
        else if (estaAdentro(p, polygon))
            cout << "INSIDE\n";
        else
            cout << "OUTSIDE\n";
    }
    return 0;
}
