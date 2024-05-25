#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define DBG(x) cerr << #x << " = " << (x) << endl

using tint = long long;

const int MAXN = 110000;
typedef unsigned char xchar;
char s[MAXN];

namespace Notebook
{
    int p[MAXN], r[MAXN], h[MAXN], t, n;

    bool sacmp(int a, int b) { return p[(a+t)%n] < p[(b+t)%n]; }
    void bwt(int nn) {
        n = nn;
        int bc[256];
        memset(bc, 0, sizeof(bc));
        forn(i, n) ++bc[int(s[i])];
        forn(i, 255) bc[i+1]+=bc[i];
        forn(i, n) r[--bc[int(s[i])]]=i;
        forn(i, n) p[i]=bc[int(s[i])];
        
        int lnb,nb = 1;
        for(t = 1; t < n; t*=2) {
            lnb = nb; nb = 0;
            for(int i = 0, j = 1; i < n; i = j++) {
                /*calcular siguiente bucket*/
                while(j < n && p[r[j]] == p[r[i]]) ++j;
                if (j-i > 1) {
                    sort(r+i, r+j, sacmp);
                    int pk, opk = p[(r[i]+t)%n];
                    int q = i, v = i;
                    for(; i < j; i++) {
                        if (((pk = p[(r[i]+t)%n]) != opk) && !(q <= opk && pk < j)) { opk = pk; v = i; }
                        p[r[i]] = v;
                    }
                }
                nb++;
            }
            if (lnb == nb) break;
        }
    //	prim = p[0];
    }

    void lcp() {
        int q = 0, j;
        forn(i,n) if (p[i]) {
            j = r[p[i]-1];
            while(q < n && s[(i+q)%n] == s[(j+q)%n]) ++q;
            h[p[i]-1] = q;
            if (q > 0) --q;
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    int N = int(strlen(s));
    tint k;
    cin >> k;
    Notebook::bwt(N+1);
    Notebook::lcp();
    forsn(i, 1, N+1)
    {
        int start = Notebook::r[i] + Notebook::h[i-1];
        int newSubstrings = N - start;
        assert(newSubstrings >= 0);
        if (newSubstrings >= k)
        {
            s[start + k] = 0;
            cout << s + Notebook::r[i] << "\n";
            return 0;
        }
        else
            k -= newSubstrings;
    }
    assert(false);
}
