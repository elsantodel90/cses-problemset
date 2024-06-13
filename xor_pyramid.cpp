#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>
#include <cassert>
#include <vector>
#include <list>

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

const int MAXN = 200000;
int factorial[MAXN+1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    factorial[0] = 0;
    forn(i,MAXN)
    {
        factorial[i+1] = factorial[i];
        int x = i+1;
        while (x % 2 == 0)
        {
            x /= 2;
            factorial[i+1]++;
        }
    }
    int n;
    cin >> n;
    int ret = 0;
    forn(i,n)
    {
        int x;
        cin >> x;
        int e = factorial[n-1] - factorial[i] - factorial[n-1-i];
        assert(e >= 0);
        ret ^= (e == 0) * x;
    }
    cout << ret << "\n";
    return 0;
}
