#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define all(c) (c).begin(), (c).end()

typedef long long tint;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> v(n);
    forn(i,n)
        cin >> v[i];
    sort(all(v));
    tint k = 0;
    for (int x : v)
    {
        if (x > k+1)
            break;
        k += x;
    }
    cout << k+1 << "\n";
    
    return 0;
}
