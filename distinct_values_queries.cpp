#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=(n)-1;i>=(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int MAX_NODES = 50000000;

int queryA, queryB;
int updateI, updateValue;

struct ST;
const ST* newNode(int s, const ST*left, const ST*right);

struct ST
{
    int s;
    const ST *left;
    const ST *right;
    
    const ST *update(int a, int b) const
    {
        if (b <= updateI || a > updateI)
            return this;
        if (a == updateI && b == updateI+1)
            return newNode(updateValue, left, right);
        int mid = (a+b)/2;
        const ST *l = left->update(a,mid);
        const ST *r = right->update(mid,b);
        return newNode(l->s + r->s, l, r);
    }
    
    int query(int a, int b) const
    {
        if (queryA <= a && b <= queryB)
            return s;
        if (b <= queryA || a >= queryB)
            return 0;
        int mid = (a+b)/2;
        return left->query(a,mid) + right->query(mid,b);
    }

};

deque<ST> nodes;

int totalNodes = 0;
const ST* newNode(int s, const ST*left, const ST*right)
{
    return new ST{s,left,right};
}


vector<const ST*> st;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ST root{0, &root, &root};
    st.push_back(&root);
    
    int n,q;
    cin >> n >> q;
    int N = 1;
    while (N < n+1)
        N *= 2;
    map<int, int> ult;
    forn(i,n)
    {
        int x;
        cin >> x;
        updateI = i+1; updateValue = 1;
        const ST *nst = st.back()->update(0, N);
        updateI = ult[x]; updateValue = 0;
        st.push_back(nst->update(0, N));
        ult[x] = i+1;
    }
    
    forn(queryIndex, q)
    {
        cin >> queryA >> queryB;
        const ST *s = st[queryB];
        queryB++;
        cout << s->query(0,N) << "\n";
    }
    
    return 0;
}
