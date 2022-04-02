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

template <typename T>
ostream & operator <<(ostream &os, const vector<T> &v)
{
    os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}


vector<int> v;

struct Range
{
    int from, to;
    
    int first() const { return v[from]; }
    int last() const { return v[to-1]; }
    bool allSame(int testBit) const { return (first() & testBit) == (last() & testBit); }
    bool allIdentical() const { return first() == last(); }
    bool getSameBit(int testBit) const { assert(allSame(testBit)); return first() & testBit; }
    
    pair<Range,Range> split(int testBit) const
    {
        int a = from;
        int b = to-1;
        assert(!(v[a] & testBit));
        assert(v[b] & testBit);
        while (b-a > 1)
        {
            int c = (a+b)/2;
            if (v[c] & testBit)
                b = c;
            else
                a = c;
        }
        return {Range{from, b}, Range{b, to}};
    }
};

const int MAX_BIT = 29;
int best;

void go(int testBit, Range a, Range b)
{
    if (testBit)
    {
        bool aSame = a.allSame(testBit);
        bool bSame = b.allSame(testBit);
        if (aSame && bSame)
            go(testBit>>1, a,b);
        else if (aSame || bSame) // Premature optimization... Separating this case makes complexity N * (lg N + MAX_BIT) instead of N * lg N * MAX_BIT
        {
            if (bSame)
                swap(a,b);
            auto split = b.split(testBit);
            go(testBit >> 1, a, a.getSameBit(testBit) ? split.first : split.second );
        }
        else
        {
            auto aSplit = a.split(testBit);
            auto bSplit = b.split(testBit);
            go(testBit>>1, aSplit.first , bSplit.second);
            go(testBit>>1, aSplit.second, bSplit.first );
        }
    }
    else
        best = max(best, a.first() ^ b.first());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    v.resize(n+1);
    v[0] = 0;
    forn(i,n)
    {
        cin >> v[i+1];
        v[i+1] ^= v[i];
    }

    sort(all(v));
    best = 0;
    go(1<<MAX_BIT, {0,n+1}, {0,n+1});
    cout << best << "\n";
    return 0;
}
