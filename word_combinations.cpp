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

struct Trie
{
    map<char, Trie> children;
    bool isWord;
    
    Trie() { isWord = false; }
    
    void putWord(const char *cad)
    {
        if (*cad == 0)
            isWord = true;
        else
            children[*cad].putWord(cad+1);

    }
    
    const Trie *go(char c) const
    {
        auto it = children.find(c);
        return it == children.end() ? nullptr : &it->second;
    }
    
    
} root;

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
    forn(i,k)
    {
        string cad; cin >> cad;
        root.putWord(cad.c_str());
    }
        
    forn(i,n)
    {
        const Trie *trieNode = &root;
        forsn(j,i+1,n+1)
        {
            // test bigWord[i:j] == bigWord.substr(i,j-i)
            trieNode = trieNode->go(bigWord[j-1]);
            if (!trieNode)
                break;
            if (trieNode->isWord)
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
