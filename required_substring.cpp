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

const int SIGMA = 26;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    string S;
    cin >> N >> S;
    int m = SIZE(S);
    
    vector<int> s(m);
    forn(i,m)
    {
        s[i] = 1;
        forn(j, m-i)
        if (S[m-1-j] != S[m-1-i-j])
        {
            s[i] = 0;
            break;
        }
    }
    
    vector<tint> f(N+1), g(N+1);
    vector<tint> potsigma(N+1);
    potsigma[0] = 1;
    forn(i,N)
        potsigma[i+1] = (potsigma[i] * SIGMA) % MOD;
    
    f[0] = 0;
    g[0] = 1;
    forsn(n, 1, N+1)
    {
        // calculo f
        f[n] = 0;
        forn(p, n-m+1)
        {
            f[n] += g[p] * potsigma[n-p-m];
            f[n] %= MOD;
        }
        // calculo g
        g[n] = (potsigma[n] - f[n]) % MOD;
        forsn(i, 1, min(m, n+1))
        {
            g[n] -= g[n-i] * s[i];
            g[n] %= MOD;
        }
    }
    cout << (f[N] + MOD) % MOD << "\n";
    return 0;
}
