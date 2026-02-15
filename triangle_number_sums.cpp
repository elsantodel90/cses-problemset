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

const tint MAXN = 1'000'000'000'000LL;

vector<tint> tri;

bool dos(tint n)
{
    for (int i=0, j=SIZE(tri)-1; i<=j; )
    {
        tint s = tri[i] + tri[j];
        if (s == n)
            return true;
        else if (s > n)
            j--;
        else
            i++;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    for (tint x=1, y=1; y < MAXN; x++, y+=x)
        tri.push_back(y);
    
    int t;
    cin >> t;
    forn(i,t)
    {
        tint n;
        cin >> n;
        if (find(ALL(tri), n) != end(tri))
            cout << "1\n";
        else if (dos(n))
            cout << "2\n";
        else
            cout << "3\n";
    }
    return 0;
}
