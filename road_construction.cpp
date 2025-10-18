#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 100000;

int parent[MAXN];
int cSize[MAXN];
int components;
int largest;

int root(int x)
{
    if (parent[x] == x)
        return x;
    else
        return parent[x] = root(parent[x]);
}

void join(int x, int y)
{
    int rx = root(x);
    int ry = root(y);
    if (rx != ry)
    {
        components--;
        parent[rx] = ry;
        cSize[ry] += cSize[rx];
        largest = max(largest, cSize[ry]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; cin >> n >> m;
    forn(i,n)
    {
        parent[i] = i;
        cSize[i] = 1;
    }
    components = n;
    largest = 1;
    forn(i,m)
    {
        int x,y;
        cin >> x >> y;
        join(x-1, y-1);
        cout << components << " " << largest << "\n";
    }
    return 0;
}
