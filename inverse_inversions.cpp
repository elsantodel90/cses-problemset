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
    tint n,k;
    cin >> n >> k;
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        tint inver = n-1-i;
        if (inver <= k)
        {
            cout << n-i;
            k -= inver;
        }
        else
        {
            int skipped = 0;
            forsn(j, 1, n-i+1)
            {
                if (j > 1)
                    cout << " ";
                if (j == n-i-k)
                {
                    cout << n-i;
                    skipped = 1;
                }
                else
                    cout << j - skipped;
            }
            break;
        }
    }
    cout << "\n";
    return 0;
}
