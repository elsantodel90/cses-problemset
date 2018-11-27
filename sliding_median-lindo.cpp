#include <iostream>
#include <set>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 1000000;
const int INF = 1000100000;

int x[MAXN];

multiset<int> low,high;
int targetLowSize;

int rebalance()
{
    while (int(low.size()) > targetLowSize)
    {
        high.insert(*low.rbegin());
        low.erase(prev(low.end()));
    }
    return *high.begin();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k; cin >> n >> k;
    forn(i,n)
        cin >> x[i];
    high.insert(INF);
    low.insert(-INF);
    forn(i,k)
        low.insert(x[i]);
    targetLowSize = 1 + (k-1)/2;
    cout << rebalance();
    forn(i, n-k)
    {
        // El i se va de donde este, entra el i+k
        auto it = low.find(x[i]);
        if (it == low.end())
            high.erase(high.find(x[i]));
        else
            low.erase(it);
        // Insertar a la izquierda: una forma segura de hacer eso es insertar a la derecha, luego pasar uno a la izquierda.
        high.insert(x[i+k]);
        low.insert(*high.begin());
        high.erase(high.begin());
        cout << " " << rebalance();
    }
    cout << "\n";
    return 0;
}
