#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

typedef long long tint;
const int MAXN = 500000;

int v[MAXN];
int n;

tint fenwick[MAXN];

tint fenwickGet(int x)
{
    tint ret = 0;
    while (x)
    {
        ret += fenwick[x];
        x = (x-1)&x;
    }
    return ret;
}

void fenwickAdd(int x)
{
    for (x++ ; x < MAXN ; x += (x&(-x)))
        fenwick[x]++;
}

tint inversions()
{
    tint ret = 0;
    dforn(i,n)
    {
        ret += fenwickGet(v[i]);
        fenwickAdd(v[i]);
    }
    return ret;
}

int greedySort()
{
    static int vcopy[MAXN];
    forn(i,n)
        vcopy[i] = v[i]-1;
    int ret = 0;
    forn(i,n)
    while (vcopy[i] != i)
    {
        ret += 1;
        swap(vcopy[i], vcopy[vcopy[i]]);
    }
    return ret;
}

int lis()
{
    int ret = 0;
    static int stackTop[MAXN];
    forn(i,n)
    {
        int x = v[i];
        int a = -1, b = ret;
        while (b-a > 1)
        {
            int c = (a+b)/2;
            if (stackTop[c] > x)
                b = c;
            else
                a = c;
        }
        if (b == ret)
            ret++;
        stackTop[b] = x;
    }
    return ret;
}

int greedySearch()
{
    int ret = n;
    dforn(i,n)
    if (v[i] == ret)
        ret--;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    forn(i,n)
        cin >> v[i];
    cout << inversions() << " " << greedySort() << " " << n - lis() << " " << greedySearch() << endl;
    return 0;
}
