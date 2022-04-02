#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MAX = 201000;

tint fenwick[MAX]; // Fenwick[i] guarda la suma [i&(i-1), i)
tint original[MAX];

#define lastBit(x) ((x)&(-x))

tint prefixSum(int i) // Suma [0, i)
{
    tint ret = 0;
    for (; i > 0 ; i -= lastBit(i))
        ret += fenwick[i];
    return ret;
}

void fenwickAdd(int i, tint x) // v[i] += x
{
    for (i++ ; i < MAX ; i += lastBit(i))
        fenwick[i] += x;
}

tint query(int i, int j)
{
    return prefixSum(j) - prefixSum(i);
}

void update(int i, tint u)
{
    fenwickAdd(i, u - original[i]);
    original[i] = u;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int N,Q;
    cin >> N >> Q;
    forn(i,N)
    {
        tint x;
        cin >> x;
        update(i, x);
    }
    
    forn(i,Q)
    {
        int t;
        cin >> t;
        if (t == 2)
        {
            int a,b;
            cin >> a >> b;
            cout << query(a-1,b) << "\n";
        }
        else if (t == 1)
        {
            int k;
            tint u;
            cin >> k >> u;
            update(k-1, u);
        }
        else
            assert(false);
    }
	return 0;
}
