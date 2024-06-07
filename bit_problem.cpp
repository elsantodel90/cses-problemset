#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <bitset>
#include <numeric>
#include <cassert>
#include <cmath>

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
#define ALL(c) (c).begin(), (c).end()

struct Data
{
    int normal, complement;
    
    Data &operator +=(const Data &o)
    {
        normal += o.normal;
        complement += o.complement;
        return *this;
    }
};

const int MAX_BITS = 20;
const int TABLE_SIZE = 1<<MAX_BITS;
#define COMPLEMENT(x) ((~(x))&(TABLE_SIZE-1))

Data t[TABLE_SIZE];


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> v(n);
    forn(i,n)
    {
        cin >> v[i];
        t[v[i]].normal++;
        t[COMPLEMENT(v[i])].complement++;
    }
    // All four implementations took the same time in cses tests as single iteration runs too fast
    // Implementation 0: 146ms for 30 runs
    forn(bit, MAX_BITS)
    for (int preMask = 0; preMask < TABLE_SIZE; preMask += 1<<(bit+1))
    forsn(mask, preMask, preMask + (1<<bit))
        t[mask | (1<<bit)] += t[mask];
    // Implementation 1: 170ms for 30 runs
    //forn(bit, MAX_BITS)
    //for (int preMask = 0; preMask < TABLE_SIZE; preMask += 1<<(bit+1))
    //forn(postMask, 1<<bit)
    //{
    //    int mask = preMask | postMask;
    //    t[mask | (1<<bit)] += t[mask];
    //}
    // Implementation 2:  200ms for 30 runs
    //forn(bit, MAX_BITS)
    //forn(unAdjustedMask, 1<<(MAX_BITS-1))
    //{
    //    int mask = (unAdjustedMask & ((1<<bit)-1)) | ((unAdjustedMask &~((1<<bit)-1))<<1);
    //    t[mask | (1<<bit)] += t[mask];
    //}
    // Implementation 3: 280ms for 30 runs
    //forn(bit, MAX_BITS)
    //forn(mask, TABLE_SIZE)
    //if (!(mask & (1<<bit)))
    //    t[mask | (1<<bit)] += t[mask];
    for (int x : v)
        cout << t[x].normal << " " << t[COMPLEMENT(x)].complement << " " << n - t[COMPLEMENT(x)].normal << "\n";
    
    return 0;
}
