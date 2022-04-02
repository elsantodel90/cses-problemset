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

struct Item
{
    int index, value;
};

vector<int> prevLower(const vector<int> &v)
{
    vector<int> ret(SIZE(v), -1);
    forn(i, SIZE(ret))
    dforn(j,i)
    if (v[j] < v[i])
    {
        ret[i] = j;
        break;
    }
    return ret;
}

//vector<int> prevLower(const vector<int> &v)
//{
//    vector<int> ret(SIZE(v));
//    stack<Item> s;
//    s.push({-1, -1});
//    forn(i, SIZE(v))
//    {
//        while (s.top().value >= v[i])
//            s.pop();
//        ret[i] = s.top().index;
//        s.push({i, v[i]});
//    }
//    return ret;
//}

vector<int> nextLower(vector<int> v)
{
    reverse(all(v));
    vector<int> ret = prevLower(v);
    reverse(all(ret));
    forn(i, SIZE(ret))
        ret[i] = SIZE(ret) - 1 - ret[i];
    return ret;
}

int maxArea(const vector<int> &v)
{
    vector<int> pl = prevLower(v);
    vector<int> pr = nextLower(v);
    int ret = 0;
    forn(i, SIZE(v))
        ret = max(ret, (pr[i] - pl[i] - 1) * v[i]);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    vector<int> v(m, 0);
    int ret = 0;
    forn(i,n)
    {
        string row;
        cin >> row;
        forn(j,m)
        if (row[j] == '*')
            v[j] = 0;
        else if (row[j] == '.')
            v[j]++;
        else
            assert(false);
        ret = max(ret, maxArea(v));
    }
    
    cout << ret << "\n";
        
    return 0;
}
