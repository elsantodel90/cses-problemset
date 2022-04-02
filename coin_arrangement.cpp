#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;
typedef vector<int> vint;

tint median(tint a,tint b,tint c)
{
    return a ^ b ^ c ^ min(a,min(b,c)) ^ max(a,max(b,c));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vint v[2] = {vint(n), vint(n)};
    forn(i,2)
    forn(j,n)
    {
        cin >> v[i][j];
        v[i][j]--;
    }
        
    tint previous = 0;
    tint ret = 0;
    tint s = 0;
    forn(i,n)
    {
        s += v[0][i] + v[1][i];
        tint t = previous + v[0][i];
        tint x = median(0, s, t);
        ret += abs(x);
        ret += abs(x-s);
        ret += abs(x-t);
        previous = x;
    }
    assert(previous == 0); // nonzero means totalCoins != 2*n
    cout << ret << "\n";
    return 0;
}
