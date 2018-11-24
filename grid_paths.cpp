#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)


typedef long long tint;

const int MOD = 1000000007;
const int MAXN = 1000010;    
const int MAXM = 1024;
    
int fact[2*MAXN], invFact[MAXN], paths[MAXM];

struct Trap
{
    int x,y;
    bool operator<(const Trap &o) const { return (x != o.x) ? (x < o.x) : (y < o.y); }
} traps[MAXM];
    
int freePaths(Trap p1, Trap p2)
{
    int verMoves = p2.x-p1.x;
    int horMoves = p2.y-p1.y;
    return int((((tint(fact[verMoves + horMoves]) * invFact[horMoves])%MOD) * invFact[verMoves]) % MOD);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    fact[0] = 1;
    forsn(i, 1,2*MAXN)
        fact[i] = int((tint(fact[i-1]) * i)%MOD);
    invFact[0] = 1;
    forn(i,MAXN)
    {
        int e = MOD-2;
        tint b = fact[i];
        invFact[i] = 1;
        while (e > 0)
        {
            if (e%2)
                invFact[i] = int((invFact[i] * b) % MOD);
            b = (b*b)%MOD;
            e /= 2;
        }
    }
    
    int n,m;
    cin >> n >> m;
    
    traps[0] = {1,1};
    forn(i,m)
        cin >> traps[i+1].x >> traps[i+1].y;
    sort(traps, traps+m+1);
    dforn(i,m+1)
    {
        paths[i] = freePaths(traps[i], {n,n});
        forsn(j, i+1,m+1)
            if (traps[j].x >= traps[i].x && traps[j].y >= traps[i].y)
                paths[i] = int((paths[i] + MOD - (tint(freePaths(traps[i], traps[j])) * paths[j])%MOD) % MOD);
    }
    cout << paths[0] << endl;
    
    return 0;
}
