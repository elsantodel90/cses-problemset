#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

const int MAXN = 1<<18;

int segtree[2*MAXN];

int INF = 1000000000;

int query(int a,int b)
{
    int ret = INF; 
    a += MAXN;
    b += MAXN;
    while (b-a > 0)
    {
        if (a%2)
            ret = min(ret, segtree[a++]);
        if (b%2)
            ret = min(ret, segtree[--b]);
        a /= 2;
        b /= 2;
    }
    return ret;
}

void replace(int pos, int newVal)
{
    pos += MAXN;
    segtree[pos] = newVal;
    while (pos > 1)
    {
        pos /= 2;
        segtree[pos] = min(segtree[2*pos], segtree[2*pos+1]);
    }
}

void init()
{
    dforn(i,MAXN)
        segtree[i] = min(segtree[2*i], segtree[2*i+1]);
}

int h[MAXN], r[MAXN], sortedQueries[MAXN];
priority_queue<int, vector<int>, greater<int>> pq[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    forn(i, N)
        cin >> h[i];
    forn(i, M)
    {
        cin >> r[i];
        sortedQueries[i] = r[i];
    }
    sortedQueries[M] = 0;
    sort(sortedQueries, sortedQueries+M+1);
    #define value(x) int(prev(upper_bound(sortedQueries, sortedQueries+M+1, (x))) - sortedQueries)
    forn(i,MAXN)
    {
        segtree[MAXN+i] = INF;
        pq[i].push(INF);
    }
    dforn(i, N)
    {
        int idx = value(h[i]);
        segtree[MAXN + idx] = i;
        pq[idx].push(i);
    }
    init();
    forn(i,M)
    {
        if (i > 0)
            cout << " ";
        int idx = value(r[i]);
        int hotel = query(idx, MAXN);
        if (hotel == INF)
            cout << 0;
        else
        {
            int cap = value(h[hotel]);
            assert(!pq[cap].empty());
            assert(hotel == pq[cap].top());
            pq[cap].pop();
            replace(cap, pq[cap].top());
            h[hotel] -= r[i];
            assert(h[hotel] >= 0);
            cap = value(h[hotel]);
            pq[cap].push(hotel);
            if (pq[cap].top() == hotel)
                replace(cap, hotel); 
            cout << hotel+1;
        }
    }
    cout << endl;
    return 0;
}
