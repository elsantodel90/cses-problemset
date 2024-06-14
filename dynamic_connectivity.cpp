#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cassert>
 
using namespace std;
 
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
 
#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)


// ROLLBACK UNION FIND
    const int MAXN = 100000;

    struct UnionFind
    {
        int parent, rank;
    };

    UnionFind uf[MAXN+1]; // uf[MAXN] is assignable dummy sentinel
    int componentCount;
    
    struct RollbackData
    {
        int child, parent, oldParentRank;
        void apply() const
        {
            componentCount += child != MAXN;
            uf[parent].rank = oldParentRank;
            uf[child].parent = child;
        }
    };

    vector<RollbackData> rollbackLog;

    void rollback()
    {
        rollbackLog.back().apply();
        rollbackLog.pop_back();
    }

    int root(int x)
    {
        while (uf[x].parent != x)
            x = uf[x].parent;
        return x;
    }

    void mergeRoots(int a, int b)
    {
        if (a == b)
            rollbackLog.push_back({MAXN, MAXN, 0});
        else
        {
            componentCount--;
            RollbackData rb;
            if (uf[a].rank < uf[b].rank)
                rb = {a, b, uf[b].rank};
            else
                rb = {b, a, uf[a].rank};
            uf[rb.child].parent = rb.parent;
            uf[rb.parent].rank += uf[a].rank == uf[b].rank;
            rollbackLog.push_back(rb);
        }
    }

    void merge(int a, int b)
    {
        mergeRoots(root(a), root(b));
    }

    void unionFindInit(int n, int q)
    {
        componentCount = n;
        forn(i,n)
            uf[i] = {i, 0};
        rollbackLog.clear();
        rollbackLog.reserve(q);
    }

// Offline Dynamic Connectivity

struct EdgeEvent
{
    int a, b;
    int t1, t2;

    bool contains(int tA, int tB) const { return t1 <= tA && tB <= t2;}
    void join() const { merge(a, b); }
    
    bool otherEdge(const EdgeEvent &o) const { return a != o.a || b != o.b; }
    #define CMP(x) if (x != o.x) return x < o.x
    bool operator<(const EdgeEvent &o) const { CMP(a); CMP(b); CMP(t1); return false; }
};

struct QueryEvent
{
    int t, node, ret;
    void find() { ret = node < 0 ? componentCount : root(node); }
};

vector<EdgeEvent> edgeEvents; 
vector<QueryEvent> queries; 
int T;
QueryEvent *nextQuery;
bool lastEventWasFlip;

void dcInit(int n, int q)
{
    T = 0;
    lastEventWasFlip = false;
    edgeEvents.clear();
    edgeEvents.reserve(q);
    queries.clear();
    queries.reserve(q+1);
    unionFindInit(n, q);
}

void flipEdge(int a, int b)
{
    lastEventWasFlip = true;
    if (a > b)
        swap(a,b);
    edgeEvents.push_back({a, b, T, T});
}

const int COMPONENT_COUNT = -1; // Use node -1 to query componentCount instead
void queryComponent(int node) 
{ 
    T += lastEventWasFlip;
    queries.push_back({T-1, node, -1});
    lastEventWasFlip = false;
}


// DCDC = Divide and Conquer Dynamic Connectivity
// Returns pointer p such that [p, b) are the ones "reaching time t2"
EdgeEvent* DCDC(EdgeEvent *a, EdgeEvent *b, int t1, int t2)
{
    #define DO_JOINS(a,b) for (EdgeEvent *p = a; p < b; p++) p->join();
    #define DO_ROLLBACKS(a,b) for (EdgeEvent *p = a; p < b; p++) rollback();
    EdgeEvent *i = a, *i2, *j;
    if (t2-t1 == 1)
    {
        DO_JOINS(a,b);
        while (nextQuery->t == t1) nextQuery++->find();
        DO_ROLLBACKS(a,b);
        j = a;
        i2 = b;
    }
    else
    {
        int mid = (t1+t2)/2;
        i2 = a; j = b;
        // [a,i) go left (some also right)
        // [i, i2) go only right
        // [i2, j) remains to be checked
        // [j, b) contain whole interval
        while (i2 < j)
        {
            if (i2->contains(t1,t2))
                swap(*i2, *--j);
            else if (i2->t1 < mid)
                swap(*i++, *i2++);
            else
                i2++;
        }
        DO_JOINS(j, b);
        i = DCDC(a, i, t1, mid);
        i = DCDC(i, j, mid, t2);
        DO_ROLLBACKS(j, b);
        i2 = b;
    }
    // [i,j) reach t2
    // [j,i2) remains to be checked
    // [i2, b) reach t2
    while (j < i2)
    {
        if ((i2-1)->t2 > t2)
            i2--;
        else if (i < j)
            swap(*i++, *--i2);
        else
            swap(*i++, *(i2-1)), j++;
    }
    return i;
}

void dynamicConnectivity()
{
    queries.push_back({T, -1, -1});
    int start;
    for (start = 0; queries[start].t < 0; start++)
        queries[start].find();
    nextQuery = queries.data() + start;
    while (!edgeEvents.empty() && edgeEvents.back().t1 >= T) edgeEvents.pop_back();
    sort(ALL(edgeEvents));
    int i = 0, groupStart = 0;
    forn(j, SIZE(edgeEvents))
    if (j+1 >= SIZE(edgeEvents) || edgeEvents[j+1].otherEdge(edgeEvents[j]))
    {
        for (int p = groupStart; p <= j; p += 2, i++)
        {
            edgeEvents[i] = edgeEvents[p];
            edgeEvents[i].t2 = p == j ? T : edgeEvents[p+1].t1;
        }
        groupStart = j+1;
    }
    if (T > 0)
        DCDC(edgeEvents.data(), edgeEvents.data() + i, 0, T);
    queries.pop_back(); // Remove sentinel false query at time T
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m,k;
    cin >> n >> m >> k;
    dcInit(n, m+k);
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        flipEdge(a-1,b-1);
    }
    queryComponent(COMPONENT_COUNT);
    forn(i,k)
    {
        int t,a,b;
        cin >> t >> a >> b;
        flipEdge(a-1,b-1);
        queryComponent(COMPONENT_COUNT);
    }
    dynamicConnectivity();
    forn(i, SIZE(queries))
    {
        if (i > 0)
            cout << " ";
        cout << queries[i].ret;
    }
    cout << "\n";
    return 0;
}
