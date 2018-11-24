#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

const int MAXN = 1000000;

int v[MAXN];

int n,k;

bool ok(tint bound)
{
    tint current = 0;
    tint total = 1;
    forn(i,n)
    {
        current += v[i];
        if (current > bound)
        {
            total++;
            current = v[i];
        }
    }
    return total <= k;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    forn(i,n)
        cin >> v[i];
    tint a=0, b = 10000000000000000LL;
    forn(i,n)
        a = max(a,tint(v[i]-1));
    while (b-a>1)
    {
        tint c = (a+b)/2;
        if (ok(c))
            b = c;
        else
            a = c;
    }
    cout << b << endl;
    return 0;
}
