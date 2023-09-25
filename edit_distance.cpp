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

const int MAX = 5050;

int f[2][MAX];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string a,b;
    cin >> a >> b;
    const int N = SIZE(a);
    const int M = SIZE(b);
    forn(j,M+1)
        f[0%2][j] = j;
    forsn(i,1,N+1)
    {
        f[i%2][0] = i;
        forsn(j,1,M+1)
        {
            int value = min(f[(i-1)%2][j-1], min(f[i%2][j-1], f[(i-1)%2][j])) + 1;
            if (a[i-1] == b[j-1])
                value = min(value, f[(i-1)%2][j-1]);
            f[i%2][j] = value;
        }
    }
    cout << f[N%2][M] << "\n";
    return 0;
}
