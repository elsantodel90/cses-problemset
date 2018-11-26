#include <iostream>
#include <queue>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 1000000;

int x[MAXN];

template<int K>
struct Comp
{
    bool operator()(int i, int j) { return (x[i] != x[j]) ? (K*x[i] < K*x[j]) : (K*i < K*j); }
};

const int INF = 1000010000;

template <int K>
void clean(priority_queue<int, vector<int>, Comp<K>> &pq, int i)
{
    while (pq.top() <= i)
        pq.pop();
}

template <int K>
int top(priority_queue<int, vector<int>, Comp<K>> &pq, int i)
{
    clean(pq,i);
    return pq.top();
}

template <int K>
int pop(priority_queue<int, vector<int>, Comp<K>> &pq, int i)
{
    clean(pq,i);
    int ret = pq.top();
    pq.pop();
    return ret;
}

priority_queue<int, vector<int>, Comp<-1>> high;
priority_queue<int, vector<int>, Comp<1>> low;    
int lowSize, targetLowSize;

int rebalanceAndGetMedian(int i)
{
    while (lowSize > targetLowSize)
    {
        lowSize--;
        high.push(pop(low, i));
    }
    return top(high, i);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k; cin >> n >> k;
    forn(i,n)
        cin >> x[i];
    x[n] = INF;
    x[n+1] = -INF;
    high.push(n);
    low.push(n+1);
    forn(i,k)
        low.push(i);
    targetLowSize = 1 + (k-1)/2;
    lowSize = 1+k;
    cout << x[rebalanceAndGetMedian(-1)];
    forn(i, n-k)
    {
        // El i se va, entra el i+k
        lowSize -= Comp<1>()(i, top(high,i-1));
        high.push(i+k);
        lowSize++;
        low.push(pop(high, i));
        cout << " " << x[rebalanceAndGetMedian(i)];
    }
    cout << "\n";
    return 0;
}
