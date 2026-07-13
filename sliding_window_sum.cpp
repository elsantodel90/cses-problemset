#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)

typedef long long tint;

int x,a,b,c;
vector<int> v;

int nextNumber()
{
    v.push_back(x);
    x = int((tint(a)*x+b)%c);
    return v.back();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin >> n >> k;
    cin >> x >> a >> b >> c;
    tint s = 0;
    forn(i,k)
        s += nextNumber();
    tint ret = s;
    forn(i,n-k)
    {
        s += nextNumber();
        s -= v[i];
        ret ^= s;
    }
    
    cout << ret << "\n";
    
    return 0;
}
