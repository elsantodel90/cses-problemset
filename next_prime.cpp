#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) cerr << #x << " = " << (x) << endl

#define SIZE(c) int((c).size())
#define ALL(c) begin(c),end(c)

typedef long long tint;

map<tint, bool> cache;

bool prime(tint x)
{
    if (x < 2)
        return false;
    if (cache.count(x))
        return cache[x];
    for (tint i = 2; i * i <= x; i++)
    if (x%i == 0)
        return cache[x] = false;
    return cache[x] = true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int TT;
    cin >> TT;
    forn(tt,TT)
    {
        tint N;
        cin >> N;
        do { N++; } while (!prime(N));
        cout << N << "\n";
    }
    return 0;
}
