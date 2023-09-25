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

const int MAX = 512;
const int INF = 1000000000;

int f[MAX][MAX];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int A,B;
    cin >> A >> B;
    
    if (A > B)
        swap(A,B);
    // A <= B
    
    forsn(i, 1, B+1)
        f[i][i] = 0;
    // a < b
    forsn(a,1, A+1)
    forsn(b, a+1, B+1)
    {
        int best = INF;
        //forsn(k,1, a/2+1)
        //    best = min(best, f[k][b] + f[a-k][b]);
        forsn(k,1, b/2+1)
            best = min(best, f[min(a,k)][max(a,k)] + 
                             f[min(a, b-k)][max(a, b-k)]);
        f[a][b] = 1 + best;
    }
    
    cout << f[A][B] << "\n";;
    
    return 0;
}
