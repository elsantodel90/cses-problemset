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

#define size(c) int((c).size())
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;




struct Data
{
    int sum;
    
    Data() // NEUTRO
    {
        sum = 0;
    } 
    
    Data(int s)
    {
        sum = s;
    }
    
    Data(const Data &left, const Data &right)
    {
        sum = left.sum + right.sum;
    }
    
    void merge(const Data &left, const Data &right)
    {
        *this = Data(left, right);
    }
};

struct SegmentTree
{
    int n;
    vector<Data> st;
    
    Data *preinit(int minN)
    {
        n = 1;
        while (n < minN) n *= 2;
        st = vector<Data>(2*n);
        return &st[n];
    }
    
    void recalc(int node)
    {
        st[node].merge(st[2*node], st[2*node+1]);
    }
    
    void init()
    {
        dforn(i,n) recalc(i);
    }
    
    void update(int i) // Must be called after modifying the value
    {
        assert(0 <= i);
        assert(i < n);
        int node = n+i;
        while ((node /= 2) > 0)
            recalc(node);
    }
    
    Data &value(int i)
    {
        assert(0 <= i);
        assert(i < n);
        return st[n+i];
    }
    
    void update(int i, Data newValue)
    {
        value(i) = newValue;
        update(i);
    }
    
    Data query(int a, int b)
    {
        assert(0 <= a);
        assert(a <= b);
        assert(b <= n);
        Data leftRet;
        Data rightRet;
        a += n;
        b += n;
        while(a < b)
        {
            if (a % 2 != 0) leftRet = Data(leftRet, st[a++]);
            if (b % 2 != 0) rightRet = Data(st[--b], rightRet);
            a /= 2;
            b /= 2;
        }
        return Data(leftRet, rightRet);
    }
};

struct Query
{
    char type;
    int a,b;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,q;
    cin >> n >> q;
    
    vector<int> salaries(n);
    vector<int> comprimidas;
    #define COMPRIMIR(x) int(lower_bound(all(comprimidas), (x)) - comprimidas.begin())
    forn(i,n)
    {
        cin >> salaries[i];
        comprimidas.push_back(salaries[i]);
    }
    vector<Query> queries(q);
    
    
    
    forn(i,q)
    {
        cin >> queries[i].type >> queries[i].a >> queries[i].b;
        if (queries[i].type == '?')
            comprimidas.push_back(queries[i].a);
        comprimidas.push_back(queries[i].b);
    }
    sort(all(comprimidas));
    comprimidas.erase(unique(all(comprimidas)), comprimidas.end());

    forn(i,n)
        salaries[i] = COMPRIMIR(salaries[i]);
    forn(i,q)
    {
        if (queries[i].type == '?')
            queries[i].a = COMPRIMIR(queries[i].a);
        queries[i].b = COMPRIMIR(queries[i].b);
    }


    SegmentTree st;
    Data *base = st.preinit(size(comprimidas));
    forn(i,n)
        base[salaries[i]].sum++;
    st.init();
    for (Query query : queries)
    {
        if (query.type == '?')
            cout << st.query(query.a, query.b+1).sum << "\n";
        else
        {
            int oldSalary = salaries[query.a-1];
            int newSalary = salaries[query.a-1] = query.b;
            st.value(oldSalary).sum--;
            st.update(oldSalary);
            st.value(newSalary).sum++;
            st.update(newSalary);
        }
    }
    
    return 0;
}
