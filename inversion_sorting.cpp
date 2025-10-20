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

// [i,j)
int reverseRange(int i, int j)
{
    cout << i+1 << " " << j << endl;
    int ret;
    cin >> ret;
    if (ret == 0)
        exit(0);
    return ret;
}

int choose2(int x)
{
    return (x*(x-1))/2;
}

int inversionCount(const vector<int> &v)
{
    int ret = 0;
    forn(j, SIZE(v))
    forn(i, j)
        ret += v[i] > v[j];
    return ret;
}

int main()
{
    int n;
    cin >> n;
    int inversions = reverseRange(0, 1);
    vector<int> prefix = {0};
    int prefixInversions = 0;
    forsn(i, 1, n)
    {
        assert(SIZE(prefix) == i);
        int newInversions = reverseRange(0, i+1);
        int prefixDelta = choose2(i) - 2*prefixInversions;
        int xTerm = newInversions - inversions - prefixDelta;
        
        assert(-i <= xTerm && xTerm <= i);
        int xSize = xTerm - (-i);
        assert(xSize % 2 == 0);
        int x = xSize / 2;
        prefixInversions += prefixDelta;
        
        prefix.push_back(x);
        reverse(ALL(prefix));
        forsn(j, 1, i+1)
        if (prefix[j] >= x)
            prefix[j]++;
        else
            prefixInversions++;
        //assert(prefixInversions == inversionCount(prefix));
        inversions = newInversions;
    }
    assert(SIZE(prefix) == n);
    // Conozco todo el array
    // Panqueque sort
    forn(i,n-1)
    {
        int iIndex = int(find(ALL(prefix), i) - begin(prefix));
        assert(i <= iIndex);
        reverseRange(i, iIndex + 1);
        reverse(begin(prefix) + i, begin(prefix) + iIndex + 1);
    }
    return 0;
}
