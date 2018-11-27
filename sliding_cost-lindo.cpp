#include <iostream>
#include <set>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

const int MAXN = 1000000;
const int INF = 1000100000;

int x[MAXN];

multiset<int> low,high;
int targetLowSize;
tint sumLow = 0, sumHigh = 0;

tint rebalance()
{
    while (int(low.size()) > targetLowSize)
    {
        int elem = *low.rbegin();
        sumHigh += elem;
        sumLow -= elem;
        high.insert(elem);
        low.erase(prev(low.end()));
    }
    int median = *high.begin();
    return (sumHigh - median * high.size() ) + (median * low.size() - sumLow);
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
    {
        sumLow += x[i];
        low.insert(x[i]);
    }
    targetLowSize = 1 + (k-1)/2;
    cout << rebalance();
    forn(i, n-k)
    {
        // El i se va de donde este, entra el i+k
        auto it = low.find(x[i]);
        if (it == low.end())
        {
            sumHigh -= x[i];
            high.erase(high.find(x[i]));
        }
        else
        {
            sumLow -= x[i];
            low.erase(it);
        }
        // Insertar a la izquierda: una forma segura de hacer eso es insertar a la derecha, luego pasar uno a la izquierda.
        sumHigh += x[i+k];
        high.insert(x[i+k]);
        int elem = *high.begin();
        sumLow += elem;
        low.insert(elem);
        sumHigh -= elem;
        high.erase(high.begin());
        cout << " " << rebalance();
    }
    cout << "\n";
    return 0;
}
