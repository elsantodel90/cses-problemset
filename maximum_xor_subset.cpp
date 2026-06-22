#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=(n)-1;i>=(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

const int BITS = 30;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    forn(i,n)
        cin >> v[i];
        
    for (int i = 0, j = BITS-1; i < n && j >= 0 ; j--)
    {
        int nextKeyNumber = -1;
        forsn(k,i,n)
        if ((v[k]>>j)&1)
        {
            nextKeyNumber = k;
            break;
        }
        if (nextKeyNumber >= 0)
        {
            swap(v[nextKeyNumber], v[i]);
            forsn(k,i+1,n)
            if ((v[k]>>j)&1)
                v[k] ^= v[i];
            i++;
        }
    }
    
    int ret = 0;
    forn(i,n)
        ret = max(ret, ret^v[i]);

    cout << ret << "\n";

    return 0;
}
