#include <iostream>
#include <iomanip>
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
#define RAYA do {cerr << " =============================== " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<int> v(N);
    forn(i,N)
        cin >> v[i];
    int j = 0;
    set<int> elements;
    tint ret = 0;
    forn(i,N)
    {
        assert(j >= i);
        assert(SIZE(elements) == j-i);
        while (j < N && elements.count(v[j]) == 0)
            elements.insert(v[j++]);
        ret += SIZE(elements);
        elements.erase(v[i]);
    }
    cout << ret << "\n";
    return 0;
}
