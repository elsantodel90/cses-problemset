#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>

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
typedef vector<int> vint;
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

const int MAXN = 210000;

int compo[MAXN];

vector<int> gOrig[MAXN], gTras[MAXN];
vector<int> *g;
int currentCompo;

vector<int> finalizationOrder;

void dfs(int x)
{
    compo[x] = currentCompo;
    for (int y : g[x])
    if (compo[y] < 0)
        dfs(y);
    finalizationOrder.push_back(x);
}

int N;
vector<int> orden;

void fullDfs(vector<int> graph[])
{
    g = graph;
    currentCompo = 0;
    forn(i, N)
        compo[i] = -1;
    for (int i : orden)
    if (compo[i] < 0)
    {
        dfs(i);
        currentCompo++;
    }
}

int getNode(const string &s, int num)
{
    int ret = (num<<1);
    if (s == "+")
        ret |= 1;
    else if (s == "-")
        ret |= 0;
    else
        assert(false);
    assert(0 <= ret);
    assert(ret < N);
    return ret;
}

int neg(int x)
{
    return x^1;
}

bool isTrue(int node)
{
    return compo[node] > compo[neg(node)];
}

bool thereIsPizza()
{
    forn(i,N)
    if (compo[i] == compo[neg(i)])
        return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    

    int n,m;
    cin >> n >> m;
    N = 2*m;
    
    forn(i,n)
    {
        string s1, s2;
        int n1,n2;
        cin >> s1 >> n1 >> s2 >> n2;
        int node1 = getNode(s1,n1-1);
        int node2 = getNode(s2,n2-1);
        gOrig[neg(node1)].push_back(node2);
        gOrig[neg(node2)].push_back(node1);
    }
    forn(x,N)
    for (int y : gOrig[x])
        gTras[y].push_back(x);
    
    orden.resize(N);
    forn(i,N)
        orden[i] = i;
    fullDfs(gOrig);
    orden = finalizationOrder;
    reverse(all(orden));
    fullDfs(gTras);
    
    if (thereIsPizza())
    {
        forn(i, m)
        {
            if (i > 0)
                cout << " ";
            cout << "-+"[isTrue((i<<1)|1)];
        }
        cout << "\n";
    }
    else
        cout << "IMPOSSIBLE\n";
    
    return 0;
}
