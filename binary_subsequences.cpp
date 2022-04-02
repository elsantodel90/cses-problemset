#include <iostream>
#include <queue>
#include <map>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define esta(x,c) ((c).find(x) != (c).end())
#define SIZE(c) int((c).size())

const int INF = 1000000000;

int fastSteps(int a,int b)
{
    int total = 0;
    while (true)
    {
        assert(a >= b);
        if (a == b)
        {
            if (a == 0)
                return total;
            else
                return INF;
        }
        else
        {
            int c =  a/(b+1);
            assert(c >= 1);
            total += c;
            a %= (b+1);
            swap(a,b);
        }
    }
}

string steps(int a,int b)
{
    bool inverted = false;
    string ret;
    while (true)
    {
        assert(a >= b);
        if (a == b)
        {
            assert(a == 0);
            return ret;
        }
        else
        {
            int c =  a/(b+1);
            assert(c >= 1);
            ret += string(c, char('0' + inverted));
            a %= (b+1);
            swap(a,b);
            inverted = !inverted;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    int best = INF;
    int bestI = -1;
    forn(i,(n+1)/2)
    {
        int t = fastSteps(n-i, i);
        if (t < best)
        {
            best = t;
            bestI = i;
        }
    }
    assert(bestI >= 0);
    
    cout << steps(n-bestI, bestI) << "\n";
    return 0;
}
