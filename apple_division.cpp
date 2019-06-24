#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

tint w[32];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    tint total = 0;
    forn(i,n)
    {
        cin >> w[i];
        total += w[i];
    }
    tint minDiff = total;
    forn(mask, 1<<n)
    {
        tint s = 0;
        forn(i,n)
        if ((mask >> i) & 1)
            s += w[i];
        tint d = abs(total - 2*s);
        if (d < minDiff)
            minDiff = d;
    }
    cout << minDiff << "\n";
    return 0;
}
