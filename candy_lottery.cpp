#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <bitset>
#include <numeric>
#include <cassert>
#include <cmath>

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,k;
    cin >> n >> k;
    
    double ret = 0.0;
    forsn(m,1,k+1)
    {
        double p1 = double(m)/k;
        double p2 = double(m-1)/k;
        double pEqualM = pow(p1 , n) - pow(p2, n);
        ret += m * pEqualM;
    }
    
    cout << fixed << setprecision(6) << ret << "\n";
    
    return 0;
}
