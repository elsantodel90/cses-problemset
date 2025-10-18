#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 200000;

int v[MAXN];
struct Elem {int value, pos; bool operator<(const Elem &o) const { return value < o.value;}} elems[MAXN];

int ft[MAXN];
const int MOD = 1000000007;

int query(int x)
{
    int ret = 0;
    for (; x > 0; x -= x&(-x))
        ret = (ret+ft[x])%MOD;
    return ret;
}

void add(int x,int value)
{
    for(x++; x < MAXN; x += x&(-x))
        ft[x] = (ft[x]+value)%MOD;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    forn(i,n)
    {
        cin >> elems[i].value;
        elems[i].pos = i;
    }
    sort(elems, elems+n);
    int nextValue = 0;
    forn(i,n)
    {
        nextValue += i > 0 && elems[i].value != elems[i-1].value;
        v[elems[i].pos] = nextValue;
    }
    int ret = 0;
    forn(i,n)
    {
        int dpi = query(v[i])+1;
        ret = (ret+dpi)%MOD;
        add(v[i], dpi);
    }
    cout << ret << endl;
    return 0;
}
