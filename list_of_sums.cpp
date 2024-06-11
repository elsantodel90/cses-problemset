#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>
#include <cassert>
#include <vector>
#include <list>

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

struct HistogramItem
{
    int number;
    int count;
    
    bool operator<(const HistogramItem &o) const
    {
        return number < o.number;
    }
};

const tint MIN_VAL = 1;
const tint MAX_VAL = 1000000000;
#define IN_RANGE(x) (1 <= (x) && (x) <= MAX_VAL)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    int T = (n*(n-1))/2;
    vector<HistogramItem> histogram(T);
    forn(i,T)
    {
        cin >> histogram[i].number;
        histogram[i].count = 1;
    }
    sort(ALL(histogram));
    {
        int i = 0;
        forn(j, T)
        {
            if (j == 0 || histogram[j-1].number != histogram[j].number)
                histogram[i++] = {histogram[j].number, 1};
            else
                histogram[i-1].count++;
        }
        histogram.resize(i);
    }
    int s0 = histogram[0].number;
    int s1 = histogram[0].count >= 2 ? histogram[0].number : histogram[1].number;
    vector<HistogramItem> copy;
    int tot = histogram[0].count;
    int index = 0;
    vector<int> ret;
    ret.reserve(n);
    forsn(j,2,n)
    {
        while (tot <= j) tot += histogram[++index].count;
        int s2 = histogram[index].number;
        tint presum = tint(s0) + s1 - s2;
        if (presum % 2 != 0)
            continue;
        tint minimum = presum / 2;
        if (!IN_RANGE(minimum))
            continue;
        copy = histogram;
        ret.clear();
        ret.push_back(int(minimum));
        int nextIndex = 0;
        forn(numberCount, n-1)
        {
            while (copy[nextIndex].count == 0) nextIndex++;
            tint x = copy[nextIndex].number - minimum;
            if (!IN_RANGE(x))
                goto tryNextMinimum;
            for(int y : ret)
            {
                int s = int(x+y);
                auto it = lower_bound(copy.begin() + nextIndex, copy.end(), HistogramItem{s, 0});
                if (it == copy.end() || it->count == 0 || it->number != s)
                    goto tryNextMinimum;
                it->count--;
            }
            ret.push_back(int(x));
        }
        
        forn(i,n)
        {
            if (i > 0)
                cout << " ";
            cout << ret[i];
        }
        cout << "\n";
        return 0;
tryNextMinimum:;
    }
    assert(false);
}
