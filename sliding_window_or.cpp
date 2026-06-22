#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=(n)-1;i>=(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int BITS = 30;
const int INF = 1000000000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin >> n >> k;
    
    int ret = 0;
    
    int x,a,b,c;
    cin >> x >> a >> b >> c;
    int ts[BITS];
    forn(i,BITS)
        ts[i] = -INF;
    forn(i,n)
    {
        forn(j,BITS)
        {
            if ((x>>j)&1)
                ts[j] = i;
            
            ret ^= (1<<j) * (i >= k-1 && ts[j] >= i+1-k);
        }   
        x = int((tint(x)*a+b)%c);
    }
    
    cout << ret << "\n";
    
    return 0;
}
