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

const int primo1 = 1000030529;
const int primo2 = 1012341521;

const int BASE = 28;

struct Hash
{
    int mod1,mod2;
    
    Hash() {mod1 = mod2 = 0; }
    
    void add(char c)
    {
        mod1 = int((BASE * tint(mod1) + int(1+c-'a')) % primo1);
        mod2 = int((BASE * tint(mod2) + int(1+c-'a')) % primo2);
    }
    
    bool operator <(const Hash &o) const
    {
        if (mod1 != o.mod1)
            return mod1 < o.mod1;
        return mod2 < o.mod2;
    }
};

Hash getHash(const string &s)
{
    Hash ret;
    for (char c : s)
        ret.add(c);
    return ret;
}

const int MAXN = 6000;
const int MOD = 1000000007;

vector<int> g[MAXN];
int dp[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string bigWord; cin >> bigWord;
    const int n = int(bigWord.size());
    
    int k; cin >> k;
    vector<Hash> diccionario(k); 
    forn(i,k)
    {
        string cad; cin >> cad;
        diccionario[i] = getHash(cad);
    }
    sort(all(diccionario));
        
    forn(i,n)
    {
        Hash substringHash;
        forsn(j,i+1,n+1)
        {
            // test bigWord[i:j] == bigWord.substr(i,j-i)
            substringHash.add(bigWord[j-1]);
            if (binary_search(all(diccionario), substringHash))
                g[i].push_back(j);
        }
    }

    dp[n] = 1;
    dforn(i,n)
    {
        dp[i] = 0;
        for (int j : g[i])
            dp[i] = (dp[i] + dp[j])%MOD;
    }
        
    cout << dp[0] << "\n";
        
    return 0;
}
