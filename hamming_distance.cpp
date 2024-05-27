#pragma GCC target("popcnt")

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    cin >> n >> k;
    vector<int> v(n,0);
    string s;
    forn(i,n)
    {
        cin >> s;
        forn(j,k)
            v[i] |= (1 << j) * (s[j] == '1');
    }
    int ret = k;
    forn(j,n)
    forn(i,j)
        ret = min(ret, __builtin_popcount(v[i]^v[j]));
    cout << ret << "\n";
    return 0;
}
