#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 250000;

vector<int> g[MAXN];
int dist[2][MAXN];

int dIndex;

void dfs(int node, int parent)
{
    dist[dIndex][node] = dist[dIndex][parent]+1;
    for (int y : g[node])
    if (y != parent)
        dfs(y, node);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    forn(i,n-1)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dist[0][n] = dist[1][n] = -1;
    dIndex = 0;
    dfs(0,n);
    int A = int(max_element(dist[0], dist[0]+n) - dist[0]);
    dfs(A, n);
    dfs(A, n);
    int B = int(max_element(dist[0], dist[0]+n) - dist[0]);
    dIndex = 1;
    dfs(B, n);
    forn(i,n)
    {
        if (i > 0)
            cout << " ";
        cout << max(dist[0][i] , dist[1][i]);
    }
    cout << "\n";
    return 0;
}
