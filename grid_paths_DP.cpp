#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define SIZE(c) int((c).size())

#define DBG(x) cerr << #x << " = " << (x) << endl
#define DBG2(x,y) cerr << #x << " = " << (x) << " , " << #y << " = " << (y) << endl
#define RAYA cerr << "============================" << endl

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

const int MOD = 1000000007;

const int MAXN = 1024;

int cantFormas[MAXN][MAXN];
string grilla[MAXN];


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    forn(i,n)
        cin >> grilla[i];
    
    //grilla[0][0] = '.';  Redaccion fea???
    
    forn(i,n+1)
        cantFormas[i][n] = cantFormas[n][i] = 0;
    cantFormas[n-1][n] = 1;
    
    dforn(i,n)
    dforn(j,n)
    if (grilla[i][j] == '*')
        cantFormas[i][j] = 0;
    else
        cantFormas[i][j] = (cantFormas[i+1][j] + cantFormas[i][j+1])%MOD;
    
    cout << cantFormas[0][0] << "\n";
    
    return 0;
}
