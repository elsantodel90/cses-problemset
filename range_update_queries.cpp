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

void querySumar(int i,int j, tint u)
{
    fenwickAdd(i-1, u);
    fenwickAdd(j-1, -u);
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
        querySumar(i+1, i+2, x);
    }
    
    forn(i,Q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int a,b;
            tint u;
            cin >> a >> b >> u;
            querySumar(a,b+1, u);
        }
        else if (t == 2)
        {
            int k;
            cin >> k;
            cout << prefixSum(k) << "\n";
        }
        else
            assert(false);
    }
	return 0;
}
