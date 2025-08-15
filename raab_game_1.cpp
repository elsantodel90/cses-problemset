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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int TT;
    cin >> TT;
    forn(tt,TT)
    {
        int n,a,b;
        cin >> n >> a >> b;
        if (a+b > n || (a==0) != (b==0))
            cout << "NO\n";
        else
        {
            cout << "YES\n";
            forn(i,n)
            {
                if (i > 0)
                    cout << " ";
                cout << i+1;
            }
            cout << "\n";
            int i = 1;
            vector<int> ret;
            while (a >= 2 && b >= 2)
            {
                a -= 1;
                b -= 1;
                ret.push_back(i+1);
                ret.push_back(i);
                i += 2;
            }
            if (a == 1 || b == 1)
            {
                int delta = (a == 1) ? 1 : -1;
                int first = i; // [first, last)
                int last = i + a + b;
                while (i < last)
                {
                    int x = i + delta;
                    if (x < first)
                        x = last-1;
                    if (x >= last)
                        x = first;
                    ret.push_back(x);
                    i++;
                }
                a = b = 0;
            }
            assert(a == 0 && b == 0);
            while (i <= n)
                ret.push_back(i++);
            
            cout << ret << "\n";
        }
    }
 
    return 0;
}
