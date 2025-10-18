#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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

const int MAX_SIZE = 1024;
const int ROOT = 32;

int f[ROOT][MAX_SIZE];
int checkpoints[MAX_SIZE / ROOT+1][MAX_SIZE];
int n,m;

vector<int> a,b;

void calcRows(int i1, int i2)
{
    forsn(i,i1,i2)
    {
        forsn(j,1,m+1)
        if (a[i-1] == b[j-1])
            f[i%ROOT][j] = f[(i-1)%ROOT][j-1] + 1;
        else
            f[i%ROOT][j] = max(f[(i-1)%ROOT][j], f[i%ROOT][j-1]);
        if (i % ROOT == 0)
            forn(j,m+1)
                checkpoints[i/ROOT][j] = f[i%ROOT][j];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    a.resize(n);
    forn(i,n)
        cin >> a[i];
    b.resize(m);
    forn(j,m)
        cin >> b[j];
    
    calcRows(1, n+1);
    
    cout << f[n%ROOT][m] << "\n";
    
    vector<int> lcs;
    int nextMissing = n-ROOT;
    while (n > 0 && m > 0)
    {
        if (n-1 <= nextMissing)
        {
            // El mayor entero multiplo de ROOT,
            // que sea <= a n-1
            int iIndex = (n-1)/ROOT;
            int i = iIndex * ROOT;
            forn(j,m+1)
                f[i%ROOT][j] = checkpoints[iIndex][j];
            calcRows(i+1, n+1);
            nextMissing = i;
        }
        
        if (a[n-1] == b[m-1])
        {
            lcs.push_back(a[n-1]);
            n--;
            m--;
        }
        else if (f[(n-1)%ROOT][m] < f[n%ROOT][m-1])
            m--;
        else
            n--;
    }
    
    dforn(i,SIZE(lcs))
    {
        if (i < SIZE(lcs) - 1)
            cout << " ";
        cout << lcs[i];
    }
    cout << "\n";
    
    return 0;
}
