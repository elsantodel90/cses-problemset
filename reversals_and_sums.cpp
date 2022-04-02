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
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

template <typename T>
istream & operator >>(istream &is, vector<T>& v) {
    int n;
    is >> n;
    v.resize(n);
    forn(i,n)
        is >> v[i];
    return is;
}


vector<int> v;
vector<tint> prefixSum;

void calcPrefixSum()
{
    prefixSum.resize(v.size()+1);
    prefixSum[0] = 0;
    forn(i,v.size())
        prefixSum[i+1] = prefixSum[i] + v[i];
}

const int MAX_BLOCKS = 400;

struct Block
{
    int a,b; // a < b
    bool reversed;
    int size() const { return b-a; }
    tint sum() const { return prefixSum[b] - prefixSum[a]; }
    
    int originalCellIndex(int i) const {
        return reversed ? b-1-i : a + i;
    } 
    
    int originalCutIndex(int i) const {
        return reversed ? b-i : a + i;
    } 
};

ostream & operator <<(ostream &os, const Block& block) {
    return os << "(" << block.a << " " << block.b << " " 
                << block.reversed << ")";
}

vector<Block> blocks;
vector<Block> newBlocks;

void initializeBlocks()
{
    calcPrefixSum();
    blocks = {{0, SIZE(v), false}, {SIZE(v), SIZE(v), false}};
}

vector<int> newV;

void rebuild()
{
    newV = v;
    int j = 0;
    for (Block block : blocks)
        forn(i, block.size())
            newV[j++] = v[block.originalCellIndex(i)];
    v.swap(newV);
    initializeBlocks();
}

tint doOperation(int a,int b, bool mustReverse)
{
    // cortar
    int pos = 0;
    newBlocks.clear();
    
    vector<Block> toAdd;
    for (Block block : blocks)
    {
        bool containsA = pos < a && a < pos + block.size();
        bool containsB = pos < b && b < pos + block.size();
        int cutA = block.originalCutIndex(a-pos);
        int cutB = block.originalCutIndex(b-pos);
        if (cutA > cutB)
        {
            swap(cutA,cutB);
            swap(containsA,containsB);
        }
        toAdd.clear();
        #define ADD(c1, c2) toAdd.push_back({(c1), (c2),block.reversed})
        #define SIMPLE(c) do { ADD(block.a, (c)); ADD((c), block.b); } while (false)
        if (containsA && containsB)
        {
            ADD(block.a, cutA);
            ADD(cutA, cutB);
            ADD(cutB, block.b);
        }
        else if (containsA)
            SIMPLE(cutA);
        else if (containsB)
            SIMPLE(cutB);
        else
            toAdd.push_back(block);
        assert(!toAdd.empty());
        if (block.reversed)
            swap(toAdd[0], toAdd[toAdd.size()-1]);
        for (Block blockToAdd : toAdd)
            newBlocks.push_back(blockToAdd);
        pos += block.size();
    }
    // muevo
    blocks = newBlocks;
    pos = 0;
    tint ret = 0;
    int rangeStart = -1, rangeEnd = -1;
    forn(bindex, blocks.size())
    {
        Block block = blocks[bindex];
        if (a <= pos && pos < b)
        {
            ret += block.sum();
            if (rangeStart < 0)
                rangeStart = bindex;
        }
        else if (rangeStart >= 0 && rangeEnd < 0)
            rangeEnd = bindex;
        pos += block.size();
    }
    assert(rangeStart >= 0);
    assert(rangeEnd >= 0);
    if (mustReverse)
    {
        forsn(i, rangeStart, rangeEnd)
            blocks[i].reversed ^= 1;
        reverse(blocks.begin() + rangeStart, blocks.begin() + rangeEnd);
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,q;
    cin >> n >> q;
    v.resize(n);
    forn(i,n) cin >> v[i];
    initializeBlocks();
    newBlocks.reserve(MAX_BLOCKS + 10);
    blocks.reserve(MAX_BLOCKS + 10);
    forn(query, q)
    {
        int t, a,b;
        cin >> t >> a >> b;
        a--;
        tint ret = doOperation(a,b, t==1);
        if (t == 2)
            cout << ret << "\n";
        if (SIZE(blocks) > MAX_BLOCKS)
            rebuild();
    }
    return 0;
}
