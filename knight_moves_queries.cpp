#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    forn(i,n)
    {
        tint x,y;
        cin >> x >> y;
        if (x > y)
            swap(x,y);
        tint ret;
        if (x == 1 && y == 2)
            ret = 3;
        else if (x == 2 && y == 2)
            ret = 4;
        else if (x == 3 && y == 3)
            ret = 4;
        else
        {
            x--; y--;
            ret = max(max((x+1)/2, (y+1)/2), (x+y+2)/3);
            ret += (ret+x+y) % 2 != 0;
        }
        cout << ret << "\n";
    }
    return 0;
}
