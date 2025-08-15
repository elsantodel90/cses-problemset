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

typedef long long tint;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    //os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os;// << "]";
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

string query(int i)
{
    cout << "? " << i+1 << endl;
    string ret;
    cin >> ret;
    return ret;
}

void answer(int i)
{
    cout << "! " << i+1 << endl;
}

int main()
{
    int n;
    cin >> n;
    string BLUE = query(0);
    if (query(n-1) == BLUE)
    {
        answer(n-1);
        return 0;
    }
    
    int small = 0;
    int large = n/2;
    while (large - small > 1)
    {
        int mid = (small+large)/2;
        if (query(2*mid) == BLUE)
            small = mid;
        else
            large = mid;
    }
    // query(2*small) == BLUE
    // query(2*small+2) == RED
    answer(2*small + (query(2*small+1) != BLUE));
    return 0;
}
