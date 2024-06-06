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

typedef long long tint;

const int SIGMA = 26;

int nextId = 0;

struct HistogramDiff
{
    int c[SIGMA-1];
    
    bool operator!=(const HistogramDiff &o) const
    {
        forn(i,nextId-1)
        if (c[i] != o.c[i])
            return true;
        return false;
    }
    bool operator<(const HistogramDiff &o) const
    {
        forn(i,nextId-1)
        if (c[i] != o.c[i])
            return c[i] < o.c[i];
        return false;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int letterMapping[SIGMA];
    forn(i, SIGMA)
        letterMapping[i] = -1;
    nextId = 0;
    HistogramDiff diff;
    forn(i,SIGMA-1)
        diff.c[i] = 0;
    vector<HistogramDiff> v;
    v.reserve(SIZE(s)+1);
    v.push_back(diff);
    for (char c : s)
    {
        int index = int(c-'a');
        if (letterMapping[index] < 0)
            letterMapping[index] = nextId++;
        int i = letterMapping[index];
        if (i > 0) diff.c[i-1]++;
        if (i < SIGMA-1) diff.c[i]--;
        v.push_back(diff);
    }
    sort(ALL(v));
    tint ret = 0;
    int i = 0;
    forsn(j, 1, SIZE(v)+1)
    if (j >= SIZE(v) || v[j] != v[j-1])
    {
        ret += tint(j-i) * tint(j-i-1);
        i = j;
    }
    ret /= 2;
    cout << ret << "\n";
    
    return 0;
}
