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

#define DBG(x) cerr << #x << " = " << (x) << endl

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MAXPOT = 20;

tint pot9[MAXPOT];

tint f(tint b)
{
    assert(b >= 0);
    if (b == 0)
        return 0;
    tint x = b;
    tint d = 0;
    vector<tint> bDigits;
    while (x > 0)
    {
        bDigits.push_back(x % 10);
        x /= 10;
        d++;
    }
    reverse(all(bDigits));
    assert(bDigits[0] > 0);
    tint ret = 0;
    forn(i, d)
        ret += pot9[i];
    forn(lcp, d)
    {
        if (lcp >= 2 && bDigits[lcp-1] == bDigits[lcp-2])
            break;
        // Mis opciones son 0 a bDigits[lcp] - 1
        // Ademas tengo que ser distinto de bDigits[lcp-1]
        // Ademas si justo lcp == 0, no puedo ser 0
        tint options = bDigits[lcp] - (lcp == 0) - (lcp >= 1 && bDigits[lcp-1] < bDigits[lcp]);
        ret += options * pot9[d-lcp-1];
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pot9[0] = 1;
    forn(i,MAXPOT-1)
        pot9[i+1] = pot9[i] * 9;

    tint a,b;
    cin >> a >> b;
    cout << f(b+1) - f(a) << "\n";
    
    return 0;
}
