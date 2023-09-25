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

//const int MAXN = 110000;
const int MAXM = 128;
const int LEVELS = 2;

int _f[LEVELS][MAXM];
#define f(i,l) _f[(i)%LEVELS][l]

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<int> v(n);
    forn(i,n)
        cin >> v[i];
    
    forn(l, m+1)
        f(n,l) = 1;
    
    dforn(i,n)
    forn(l, m+1)
    {
        f(i,l) = 0;
        int minValid, maxValid;
        if (l == 0)
        {
            minValid = 1;
            maxValid = m;
        }
        else
        {
            minValid = max(1, l-1);
            maxValid = min(m, l+1);
        }
        forsn(x, minValid, maxValid+1)
        if (v[i] == 0 || x == v[i])
        {
            f(i,l) += f(i+1,x);
            f(i,l) %= MOD;
        }
    }
    
    cout << f(0,0) << "\n";
    
    return 0;
}
