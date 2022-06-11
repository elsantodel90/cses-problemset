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

const int MAX_LOG = 20;
const int MAXN = 201000;

int n;

struct Function // Endofuncion en [-1,N)
{
    int f[MAXN];
    #define ACCESO f[i+1]
    int& operator()(int i) { return ACCESO; }
    int operator()(int i) const { return ACCESO; }
};

Function componer(const Function &f1, const Function &f2)
{
    Function ret;
    forsn(x, -1, n)
        ret(x) = f1(f2(x));
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> n >> q;
    
    // fPot2[i] == f^(2^i)
    vector<Function> fPot2(MAX_LOG);
    fPot2[0](-1) = -1;
    fPot2[0](0) = -1;
    forn(i,n-1)
    {
        int x;
        cin >> x;
        fPot2[0](i+1) = x-1;
    }
    forsn(i, 1, MAX_LOG)
        fPot2[i] = componer(fPot2[i-1], fPot2[i-1]);
    forn(queryIndex, q)
    {
        int x,k;
        cin >> x >> k;
        x--;
        forn(i, MAX_LOG)
        if ((k>>i)&1)
            x = fPot2[i](x);
        if (x >= 0)
            x++;
        cout << x << "\n";
    } 
    return 0;
}
