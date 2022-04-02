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

const int MOD = 1000000007;

const int MAXN = 20;

int dp[1<<MAXN][MAXN];

int g[MAXN];
int multi[MAXN][MAXN];

const int MAXM = MAXN*MAXN;

int gg[MAXN][MAXM];
int gs[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        gg[a][gs[a]++] = b;
        multi[a][b]++;
        g[a] |= 1<<b;
    }
    
    int WINMASK = (1<<n)-1;
    
    forn(i,n-1)
        dp[WINMASK][i] = 0;
    dp[WINMASK][n-1] = 1;
    
    int aux = 0;
    
    dforn(mask, WINMASK)
    forn(i,n)
    {
        aux = 0;
        for (int submask = g[i] & ~mask; submask != 0; submask = (submask-1)&submask)
        //forn(k, gs[i])
        //if (!((mask >> gg[i][k])&1))
        {
            int j = __builtin_ctz(submask);
            //int j = gg[i][k];
            int newMask = mask | (1<<j);
            if (multi[i][j] > 1)
                aux += (tint(multi[i][j]) * dp[newMask][j])%MOD;
            else
                aux += dp[newMask][j];
            if (aux >= MOD)
                aux -= MOD;
        }
        dp[mask][i] = aux;
    }
    
    int STARTMASK = 1;
    cout << dp[STARTMASK][0] << "\n";
    
    return 0;
}
