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

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;

const int MAXN = 110000;

vector<int> g[2][MAXN];
bool visited[2][MAXN];

int n;

void go(int k)
{
    vector<int> pending;
    #define PUSH(x) do {pending.push_back(x); visited[k][x] = true;} while (false)
    PUSH(0);
    while (!pending.empty())
    {
        int x = pending.back(); pending.pop_back();
        for (int y : g[k][x])
        if (!visited[k][y])
            PUSH(y);
    }
    forn(i,n)
    if (!visited[k][i])
    {
        cout << "NO\n";
        if (k == 0)
            cout << "1 " << i+1 << "\n";
        else
            cout << i+1 << " 1\n";
        exit(0);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    cin >> n >> m;
    
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[0][a].push_back(b);
        g[1][b].push_back(a);
    }

    go(0); go(1);

    cout << "YES\n";
    
    return 0;
}
