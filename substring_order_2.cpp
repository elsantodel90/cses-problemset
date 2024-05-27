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

    const int LVL = 17;
    int vec[LVL][1<<LVL];
    int minIndex(int i, int j)
    {
        if (h[i] < h[j])
            return i;
        else
            return j;
    }
    int mn(int i, int j) { // intervalo [i,j)
        int pot = 31-__builtin_clz(j-i);
        return minIndex(vec[pot][i],vec[pot][j-(1<<pot)]);
    }
    void mn_init() {
        int mp = 31-__builtin_clz(n-1);
        forn(pot, mp) forn(x, n-1-(1<<pot)) vec[pot+1][x] = minIndex(vec[pot][x], vec[pot][x+(1<<pot)]);
    }

    void lcp() {
        int q = 0, j;
        forn(i,n) if (p[i]) {
            j = r[p[i]-1];
            while(q < n && s[(i+q)%n] == s[(j+q)%n]) ++q;
            h[p[i]-1] = q;
            if (q > 0) --q;
        }
        forn(i,n-1)
            vec[0][i] = i;
        mn_init();
    }
};

int histogram[MAXN];
int N;

void printSubstring(int start, int end)
{
    s[end] = 0;
    cout << s + start << "\n";
}

tint go(tint k, int base, int a, int b)
{
    assert(a < b);
    assert(base >= 0);
    assert(k >= 1);
    if (b-a == 1)
    {
        int pos = Notebook::r[a];
        int total = N - pos - base;
        assert(total >= 0);
        if (total >= k)
        {
            printSubstring(pos, int(pos+base+k));
            return -1;
        }
        return total;
    }
    else
    {
        int cut = Notebook::mn(a, b-1) + 1;
        int lcp = Notebook::h[cut-1];
        assert(lcp >= base);
        assert((lcp-base) * tint(b-a) <= N); // Se puede demostrar que este producto es a lo sumo N, por eso int funciona.
        int total = (lcp-base) * (b-a);
        assert(total >= 0);
        if (total >= k)
        {
            int pos = Notebook::r[a];
            printSubstring(pos, int(pos + base + (k+b-a-1)/(b-a)));
            return -1;
        }
        tint left = go(k-total, lcp, a, cut);
        if (left < 0)
            return -1;
        tint right = go(k-total-left, lcp, cut, b);
        if (right < 0)
            return -1;
        return total + left + right;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    N = int(strlen(s));
    tint k;
    cin >> k;
    Notebook::bwt(N+1);
    Notebook::lcp();
    assert(go(k, 0, 1, N+1) < 0);
    return 0;
}
