#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cassert>
 
using namespace std;
 
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
 
#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

const int MAXN = 1024;
char mat[MAXN][MAXN];
int s[MAXN][MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,q;
    cin >> n >> q;
    forn(i,n)
        cin >> mat[i];
    forn(i,n)
    forn(j,n)
        s[i+1][j+1] = (mat[i][j] == '*') + s[i+1][j] + s[i][j+1] - s[i][j];
    forn(i,q)
    {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--;
        cout << s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1] << "\n";
    }
    return 0;
}
