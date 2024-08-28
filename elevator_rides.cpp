#include <iostream>
#include <algorithm>
#include <bitset>
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
#define ALL(c) begin(c), end(c)

typedef long long tint;

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

int elevatorCapacity;

struct Cost
{
    int rides, freeCapacity;
    
    void apply(int w)
    {
        if (w > freeCapacity)
        {
            rides++;
            freeCapacity = elevatorCapacity;
        }    
        freeCapacity -= w;
    }
    
    bool operator <(const Cost &o) const { return rides < o.rides || (rides == o.rides && freeCapacity > o.freeCapacity); }
};

const int MAXN = 20;
Cost dp[1<<MAXN];

const int INF = 1000000000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> elevatorCapacity;
    vector<int> v(n);
    forn(i,n)
        cin >> v[i];
    
    dp[0] = {0, 0};
    forsn(mask, 1, (1<<n))
    {
        dp[mask] = {INF, 0};
        for (int cmask = mask; cmask != 0 ; cmask = cmask&(cmask-1))
        {
            int i = __builtin_ctz(cmask);
            int submask = mask ^ (1<<i);
            Cost cost = dp[submask];
            cost.apply(v[i]);
            if (cost < dp[mask])
                dp[mask] = cost;
        }
    }
    cout << dp[(1<<n)-1].rides << "\n";
    
    return 0;
}
