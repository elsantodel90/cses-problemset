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

struct Pair
{
    tint value;
    int pos1,pos2;
    
    bool operator<(const Pair &o) const { return value < o.value; }
};

bool okPairs(const Pair &p1, const Pair &p2)
{
    return p1.pos1 != p2.pos1 &&
           p1.pos1 != p2.pos2 &&
           p1.pos2 != p2.pos1 &&
           p1.pos2 != p2.pos2;
}

bool solve(const vector<Pair> &v, tint x)
{
    // [aStart, aEnd) valen todos aValue
    int bEnd = SIZE(v);
    for (int aStart = 0, aEnd = 1; aStart < SIZE(v); aStart = aEnd++)
    {
        tint aValue = v[aStart].value;
        while (aEnd < SIZE(v) && aValue == v[aEnd].value) aEnd++;
        tint requiredB = x-aValue;
        while (bEnd > 0 && v[bEnd-1].value > requiredB) bEnd--;
        int bStart = bEnd;
        while (bStart > 0 && v[bStart-1].value == requiredB) bStart--;
        // [bStart, bEnd) valen todos x-aValue
        
        forsn(a, aStart, aEnd)
        forsn(b, bStart, bEnd)
        if (okPairs(v[a], v[b]))
        {
            cout << v[a].pos1+1 << " " <<
                    v[a].pos2+1 << " " <<
                    v[b].pos1+1 << " " <<
                    v[b].pos2+1 << "\n";
            return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    tint x;
    cin >> n >> x;
    
    vector<Pair> v;
    v.reserve(n*n);
    vector<tint> inpu(n);
    forn(i,n)
        cin >> inpu[i];
    forn(i,n)
    forn(j,i)
    {
        assert(i != j);
        v.push_back({inpu[i]+inpu[j], i, j});
    }
    
    sort(ALL(v));
    
    if (!solve(v,x))
        cout << "IMPOSSIBLE\n";
    
    return 0;
}
