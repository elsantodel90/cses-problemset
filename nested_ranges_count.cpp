#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
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

const int NEUTRO = 0;

void init(int n)
{
    base = 1;
    while (base < n) base *= 2;
    forn(i,2*base)
        st[i] = NEUTRO;
}

struct pto
{
    int x,y;
    int id;
    
    bool operator <(const pto &o) const
    {
        if (x != o.x)
            return x < o.x;
        return y > o.y;
    }
};

void calcularCuantosLoDominan(vector<pto> &v, int ySize)
{
    init(ySize);
    sort(all(v));
    vector<int> ret(v.size());
    for (pto p : v)
    {
        ret[p.id] = query(p.y, ySize);
        st[base+p.y]++;
        for (int node = (base+p.y)/2; node >= 1; node /= 2)
            st[node] = st[2*node] + st[2*node+1];
    }
    forn(i,ret.size())
    {
        if (i > 0) cout << " ";
        cout << ret[i];
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    
    vector<pto> v(n);
    vector<int> valoresY;
    valoresY.reserve(n);
    forn(i,n)
    {
        cin >> v[i].x >> v[i].y;
        valoresY.push_back(v[i].y);
        v[i].id = i;
    }
    
    sort(all(valoresY));
    valoresY.resize(unique(all(valoresY)) - valoresY.begin());
    int nextY = int(valoresY.size());
    
    for (pto &p : v)
    {
        int a = -1, b = nextY;
        while (b - a > 1)
        {
            int c = (a+b)/2;
            if (valoresY[c] >= p.y)
                b = c;
            else
                a = c;
        }
        p.y = b;
    }
    
    
    forn(veces, 2)
    {
        for (pto &p : v)
        {
            p.x = -p.x;
            p.y = nextY-1-p.y;
        }
        calcularCuantosLoDominan(v, nextY);
    }
    
    return 0;
}
