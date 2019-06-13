#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

const int MAXN = 1024000;
typedef long long tint;

struct Node
{
    tint sum, bestPrefix, bestSuffix, best;
    Node ()
    {
        set(0);
    }
    void set(tint val)
    {
        sum = val;
        bestPrefix = bestSuffix = best = max(0LL, val);
    }
    void merge(const Node &a, const Node &b)
    {
        sum = a.sum + b.sum;
        bestPrefix = max(a.bestPrefix, a.sum + b.bestPrefix);
        bestSuffix = max(b.bestSuffix, b.sum + a.bestSuffix);
        best = max(max(a.best, b.best), a.bestSuffix + b.bestPrefix);
    }
};

Node st[MAXN];

const int BASE = 1<<18;

void recalc(int i)
{
    st[i].merge(st[2*i], st[2*i+1]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N,M; cin >> N >> M;
    forn(i,N)
    {
        tint val; cin >> val;
        st[BASE + i].set(val);
    }
    dforn(i, BASE)
        recalc(i);
    forn(q, M)
    {
        int k; tint x;
        cin >> k >> x;
        int pos = BASE + k - 1;
        st[pos].set(x);
        while (pos > 1)
        {
            pos /= 2;
            recalc(pos);
        }
        cout << st[1].best << "\n";
    }
    return 0;
}
