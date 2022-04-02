#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>

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

const int MOD = 1000000007;

int f(int N,int K)
{
    int maxInversions = (N*(N-1))/2;
    assert(0 <= K);
    assert(K <= maxInversions);
    K = min(K, maxInversions - K);
    
    typedef vector<int> Row;
    vector<int> mat[2] = {Row(K+1, 0), Row(K+1, 0)};
    mat[0][0] = 1;
    forsn(n, 1, N+1)
    {
        vector<int> &prevRow = mat[(n-1)%2];
        forn(j,K)
            prevRow[j+1] = (prevRow[j+1] + prevRow[j]) % MOD;
        forn(k,K+1)
        if (k-n >= 0)
            mat[n%2][k] = (prevRow[k] - prevRow[k-n]) % MOD;
        else
            mat[n%2][k] = prevRow[k];
    }
    return mat[N%2][K];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,k;
    cin >> n >> k;
    
    cout << (f(n,k) + MOD) % MOD << "\n";
    
    return 0;
}
