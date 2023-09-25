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
#define ALL(c) begin(c), end(c)

using tint = long long;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    cout << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    cout << "]";
    return os;
}

const int MAXN = 500000;

int totalDescendantsArray[MAXN];
vector<int> minions[MAXN];

int totalDescendants(int x)
{
    if (totalDescendantsArray[x] == 0)
    {
        totalDescendantsArray[x] = 1;
        for (int minion : minions[x])
            totalDescendantsArray[x] += totalDescendants(minion);
    }
    return totalDescendantsArray[x];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    forsn(i, 2,n+1)
    {
        int boss;
        cin >> boss;
        minions[boss].push_back(i);
    }

    forsn(i,1,n+1)
    {
        if (i > 1)
            cout << " ";
        cout << totalDescendants(i) - 1;
    }
    cout << "\n";
    
    return 0;
}
