#include <iostream>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 210000;
const int LEVELS = 30;


// jump[i][x] responde la query x,  k = 2 a la i
int jump[LEVELS][MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    forn(i,N)
    {
        cin >> jump[0][i];
        jump[0][i]--;
    }
    forn(i,LEVELS-1)
    forn(x,N)
        jump[i+1][x] = jump[i][jump[i][x]];
    
    forn(i,Q)
    {
        int x, k;
        cin >> x >> k;
        x--;
        forn(j, LEVELS)
        if ((k >> j)&1)
            x = jump[j][x];
        cout << x+1 << "\n";
    }
    
    return 0;
}
