#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

#define ALL(c) (c).begin(), (c).end()

vector<int> parent;

void init(int N)
{
    parent = vector<int>(N);
    forn(i,N)
        parent[i] = i;
}

int root(int x)
{
    if (x == parent[x])
        return x;
    else
        return parent[x] = root(parent[x]);
}

void join(int a,int b)
{
    parent[root(a)] = root(b);
}

struct Edge
{
    int a,b,c;
    bool operator <(const Edge &o) const { return c < o.c; }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N,M;
    cin >> N >> M;
    vector<Edge> edges(M);
    forn(i,M)
    {
        Edge &e = edges[i];
        cin >> e.a >> e.b >> e.c;
        e.a--;
        e.b--;
    }
    init(N);
    sort(ALL(edges));
    long long ret = 0;
    int total = 0;
    for (Edge e : edges)
    if (root(e.a) != root(e.b))
    {
        join(e.a, e.b);
        ret += e.c;
        total++;
    }
    assert(total <= N-1);
    if (total < N-1)
        cout << "IMPOSSIBLE";
    else
        cout << ret;
    cout << "\n";
    return 0;
}
