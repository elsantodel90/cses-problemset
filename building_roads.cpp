#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MAXN = 300000;

int root[MAXN];

void init(int n)
{
    forn(i,n)
        root[i] = i;
}

int find(int x)
{
    int p = root[x];
    return root[x] = p == x ? x : find(p);
}

void join(int x, int y)
{
    root[find(x)] = find(y);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m; cin >> n >> m;
    init(n);
    forn(i,m)
    {
        int x,y;
        cin >> x >> y;
        join(x-1,y-1);
    }
    vector<int> ret;
    forn(i,n)
    if (find(i) != find(0))
    {
        join(0,i);
        ret.push_back(i);
    }
    
    cout << ret.size() << "\n";
    for (int y : ret)
        cout << 1 << " " << y+1 << "\n";
    
    return 0;
}
