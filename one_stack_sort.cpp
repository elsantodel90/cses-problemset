#include <iostream>
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

vector<int> mainStreet;
    
bool works()
{
    static vector<int> lateralStreet;
    lateralStreet.clear();
    int nextTruck = 1;
    while (true)
    {
        if (!lateralStreet.empty() &&
             lateralStreet.back() == nextTruck)
        {
            nextTruck++;
            lateralStreet.pop_back();
        }
        else if (mainStreet.empty())
            break;
        else
        {
            lateralStreet.push_back(mainStreet.back());
            mainStreet.pop_back();
        }
    }
    assert(mainStreet.empty());
    return lateralStreet.empty();
}

const char *ANSWERS[2] = {"no\n","yes\n"};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0)
    {
        mainStreet.resize(n);
        forn(i,n)
            cin >> mainStreet[n-1-i];
            
        cout << ANSWERS[works()];
    }
    return 0;
}
