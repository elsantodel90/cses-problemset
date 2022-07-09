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

struct Number
{
    int value;
    int position;
    
    bool operator<(const Number &o) const { return value < o.value; }
};

bool solve(const vector<Number> &v, int x)
{
    for (Number a : v)
    {
        auto cIt = v.rbegin();
        for (Number b : v)
        if (a.position != b.position)
        {
            int requiredC = x-a.value-b.value;
            while (cIt != v.rend() && 
                    (cIt->value > requiredC ||
                     a.position == cIt->position ||
                     b.position == cIt->position)
                  )
                cIt++;
            if (cIt != v.rend() && cIt->value == requiredC)
            {
                cout << a.position+1 << 
                 " " << b.position+1 <<
                 " " << cIt->position+1 << "\n";
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,x;
    cin >> n >> x;
    
    vector<Number> v(n);
    forn(i,n)
    {
        cin >> v[i].value;
        v[i].position = i;
    }
    
    sort(ALL(v));
    
    if (!solve(v,x))
        cout << "IMPOSSIBLE\n";
    
    return 0;
}
