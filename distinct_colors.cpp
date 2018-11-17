#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 1000000;

int c[MAXN];
int total[MAXN];

vector<int> g[MAXN];
typedef unordered_set<int> setType;

void dfs(int node, int parent, setType &acumSet)
{
    setType myColours{c[node]};
    for (int neighbor : g[node])
    if (neighbor != parent)
        dfs(neighbor, node, myColours);
    total[node] = int(myColours.size());
    if (acumSet.size() < myColours.size())
        acumSet.swap(myColours);
    acumSet.insert(myColours.begin(), myColours.end());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    forn(i,N)
        cin >> c[i];
    forn(i,N-1)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    setType aux;
    dfs(0, -1, aux);
    forn(i,N)
    {
        if (i > 0)
            cout << " ";
        cout << total[i];
    }
    cout << "\n";
    return 0;
}
