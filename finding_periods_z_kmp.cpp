#include <iostream>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <cassert>
#include <vector>

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
typedef vector<int> vint;
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    const int N = SIZE(s);
    vector<int> B(N+1);
    vector<int> z(N);
    z[0] = N;
    B[0] = -1;
    int a = 1,b = 1;
    B[1] = 0;
    forsn(i, 1, N)
    {
        assert(b >= i);
        if (b == i || i + z[i-a] >= b)
        {
            while (b < N && s[b] == s[b-i])
            {
                b++;
                a = i;
                B[b] = b-a;
            }
            z[i] = b-i;
            if (b == i)
            {
                b++;
                a = b;
                B[b] = b-a;
            }
        }
        else
            z[i] = z[i-a];
    }
    
    int next = N;
    while (next != 0)
    {
        next = B[next];
        cout << N - next;
        if (next != 0)
            cout << " ";
    }
    cout << "\n";
    return 0;
}
