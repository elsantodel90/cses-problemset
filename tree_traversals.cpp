#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

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

typedef long long tint;

const int MAXN = 150000;

int position[MAXN];
int in[MAXN];
int pre[MAXN];

bool pri = true;

void print(int x)
{
    if (pri)
        pri = false;
    else
        cout << " ";
    cout << x;
}

void printPostorder(int preA, int preB, int inA, int inB)
{
    int tam = preB - preA;
    assert(tam == inB - inA);
    assert(tam >= 0);
    if (tam == 0)
        return;
    int r = pre[preA];
    int tam1 = position[r] - inA;
    printPostorder(preA+1, preA+1+tam1, inA, position[r]);
    printPostorder(preA+1+tam1, preB, position[r]+1, inB);
    print(r);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (auto& array : {pre, in})
    forn(i,n)
        cin >> array[i];
    forn(i,n)
        position[in[i]] = i;
    printPostorder(0,n,0,n);
    cout << "\n";
    return 0;
}
