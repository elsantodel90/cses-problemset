#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

using tint = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    tint n;
    cin >> n;
    assert(1 <= n);
    assert(n % 2 == 1);
    tint a = 0, b = n*n;
    while (b - a > 1)
    {
        tint c = (a+b)/2;
        tint total = 0;
        for (int i=1;i<=n;i++)
            total += min(c/i, n);
        if (total >= 1 + (n*n)/2)
            b = c;
        else
            a = c;
    }
    cout << b << "\n";
    return 0;
}
