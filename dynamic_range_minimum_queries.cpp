#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

const int MAXN = 1<<18;
const int INF = 1000000001;

int st[2*MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    forn(i,2*MAXN)
        st[i] = INF;
    int n,q;
    cin >> n >> q;
    forn(i,n)
        cin >> st[MAXN + i];
    #define CALC(i) st[i] = min(st[2*(i)], st[2*(i)+1])
    dforn(i,MAXN)
        CALC(i);
    forn(queryIndex, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int k,u;
            cin >> k >> u;
            k--;
            k += MAXN;
            st[k] = u;
            while (k > 0)
            {
                k /= 2;
                CALC(k);
            }
        }
        else if (t == 2)
        {
            int a,b;
            cin >> a >> b;
            a--;
            a += MAXN;
            b += MAXN;
            int ret = INF;
            while (a < b)
            {
                if (a % 2) ret = min(ret, st[a++]);
                if (b % 2) ret = min(ret, st[--b]);
                a /= 2;
                b /= 2;
            }
            cout << ret << "\n";
        }
        else
            assert(false);
    }
    return 0;
}
