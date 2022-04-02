#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define DBG(x) cerr << #x << " = " << (x) << endl

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MAXN = 1<<20;

int st[2*MAXN];
int base;

int query(int a, int b)
{
    a += base;
    b += base;
    int ret = 0;
    while (a < b)
    {
        if (a % 2) ret += st[a++];
        if (b % 2) ret += st[--b];
        a /= 2;
        b /= 2;
    }
    return ret;
}

// Avanzar lo mas posible pero sin agarrar mas de k unos 
int avanzar(int pos, int k)
{
    assert(st[1] > k);
    int trailing = query(pos, base);
    if (trailing <= k)
    {
        pos = 0;
        k -= trailing;
    }
    // Ya sabemos que no llega hasta el final
    assert(k >= 0);
    int node = base + pos;
    while (true)
    {
        while (node % 2 == 0)
            node /= 2;
        if (st[node] > k)
            break;
        k -= st[node++];
    }
    while (node < base)
    {
        if (st[2*node] <= k)
        {
            k -= st[2*node];
            node = 2*node+1;
        }
        else
            node = 2*node;
    }
    return node - base;
    
    //int a = pos;
    //int b = base;
    //while (b-a > 1)
    //{
    //    int c = (a+b)/2;
    //    if (query(pos, c) <= k)
    //        a = c;
    //    else
    //        b = c;
    //}
    //return a;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    base = 1;
    while (base < n) base *= 2;
    forsn(i, base, base+n)
        st[i] = 1;
    #define RECALC(i) do {st[i] = st[2*(i)] + st[2*(i)+1]; } while (false)
    dforn(i, base)
        RECALC(i);
    
    int pos = 0;    
    
    
    forn(steps,n)
    {
        pos = avanzar(pos, k % (n-steps));
        
        assert(st[base+pos] == 1);
        if (steps > 0)
            cout << " ";
        cout << pos+1;
        
        st[base+pos] = 0;
        for (int node = (base+pos)/2; node > 1; node /= 2)
            RECALC(node);
    }
    cout << "\n";
    
    return 0;
}
