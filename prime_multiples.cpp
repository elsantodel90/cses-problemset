#include <iostream>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

typedef unsigned long long tint;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    tint n;
    int k;
    cin >> n >> k;
    vector<tint> v(k);
    forn(i,k)
        cin >> v[i];
    tint ret = 0;
    forsn(mask,1,1<<k)
    {
        tint p = 1;
        forn(i,k)
        if ((mask>>i) & 1)
        {
            if (p > n/v[i])
                goto next;
            p *= v[i];
        }
        if (__builtin_popcount(mask) % 2)
            ret += n / p;
        else
            ret -= n / p;
next:;
    }
    cout << ret << "\n";
    return 0;
}
