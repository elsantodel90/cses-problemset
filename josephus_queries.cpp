#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

tint f(tint n, tint k)
{
    tint mueren = (n+1)/2;
    if (k < mueren)
        return 2*k;
    tint newN = n - mueren;
    tint index = f(newN, k - mueren);
    if (n % 2 == 0)
        return 2*index + 1;
    else if (index == newN-1)
        return 1;
    else
        return 2*index + 3;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q; cin >> q;
    forn(i,q)
    {
        tint n,k;
        cin >> n >> k;
        cout << 1 + (1+f(n,k-1))%n << "\n";
    }
    
    return 0;
}
