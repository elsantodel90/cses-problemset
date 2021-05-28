#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

struct Data
{
    tint sum;
    
    Data() // NEUTRO
    {
        sum = 0;
    }
    
    void merge(const Data &left, const Data &right)
    {
        sum = left.sum + right.sum;
    }
};

struct Lazy
{
    tint a,b; // Sumar al iesimo a * i + b, con i empezando en 1 en el rango
    
    Lazy() // NEUTRO
    {
        a = b = 0;
    }
    
    Lazy(tint aa, tint bb)
    {
        a = aa;
        b = bb;
    }
    
    void updateData(Data &data, int dataLength) const
    {
        data.sum += a * ((dataLength * tint(dataLength+1))/2) + dataLength * b;
    }
    
    pair<Lazy, Lazy> split(int leftPartSize) const
    {
        return {*this, {a, b + a*leftPartSize}};
    }
    
    void updateLazy(const Lazy &newLazy) // OJO! PUEDE NO CONMUTAR
    {
        a += newLazy.a;
        b += newLazy.b;
    }
};

const int MAXN = 300000;

struct SegmentTree
{
    struct Node
    {
        Data data;
        Lazy lazy;
    };

    struct NodeIndex
    {
        int index, a,b;
        NodeIndex left() const
        {
            return {2*index, a, mid()};
        }
        
        int mid() const { return (a+b)/2;}
        
        NodeIndex right() const
        {
            return {2*index+1, mid(), b};
        }
        
        int size() const { return b-a; }
        
        bool disjoint(int queryA, int queryB) const
        {
            return a >= queryB || b <= queryA;
        }
        
        bool full(int queryA, int queryB) const
        {
            return queryA <= a && queryB >= b;
        }
    };
    
    Node st[4*MAXN];
    int size;
    
    Node* preinit(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        forn(i, 2*size)
            st[i] = Node();
        return st + size;
    }
    
    void init()
    {
        dforn(i, size)
            st[i].data.merge(st[2*i].data, st[2*i+1].data);
    }
    
    void updateNode(const NodeIndex &node, const Lazy &lazy)
    {
        st[node.index].lazy.updateLazy(lazy);
        lazy.updateData(st[node.index].data, node.size());
    }
    
    void propagate(const NodeIndex &node)
    {
        auto childrenLazy = st[node.index].lazy.split(node.size()/2);
        updateNode(node.left(), childrenLazy.first);
        updateNode(node.right(), childrenLazy.second);
        st[node.index].lazy = Lazy();
    }
    
    Data go(const NodeIndex &node, 
            int queryA, int queryB, const Lazy &lazy)
    {
        if (node.disjoint(queryA, queryB))
            return Data();
        if (node.full(queryA, queryB))
        {
            updateNode(node, lazy);
            return st[node.index].data;
        }
        propagate(node);
        int mid = node.mid();
        Data leftData, rightData;
        if (queryA < mid && queryB > mid)
        {
            auto splitLazy = lazy.split(mid-queryA);
            leftData = go(node.left(), queryA, mid, splitLazy.first);
            rightData = go(node.right(), mid, queryB, splitLazy.second);
        }
        else
        {
            leftData = go(node.left(), queryA, queryB, lazy);
            rightData = go(node.right(), queryA, queryB, lazy);
        }
        st[node.index].data.merge(st[2*node.index].data, st[2*node.index+1].data);
        Data result;
        result.merge(leftData, rightData);
        return result;
    }
    
    NodeIndex root() const
    {
        return {1, 0, size};
    }
    
    Data update(int queryA, int queryB, const Lazy& lazy)
    {
        return go(root(), queryA, queryB, lazy);
    }
    
    Data query(int queryA, int queryB)
    {
        return update(queryA, queryB, Lazy());
    }
    
} segmentTree;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int N,Q;
    cin >> N >> Q;
    
    SegmentTree::Node* v = segmentTree.preinit(N);
    forn(i,N)
    {
        cin >> v[i].data.sum;
    }
    segmentTree.init();
        
    forn(queryNumber, Q)
    {
        int t,a,b;
        cin >> t >> a >> b;
        a--;
        
        if (t == 1)
            segmentTree.update(a,b, Lazy(1,0));
        else
            cout << segmentTree.query(a,b).sum << "\n";
    }
    
	    
	return 0;
}
