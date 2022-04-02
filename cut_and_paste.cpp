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
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << " =========================== " << endl

#define SIZE(c) int((c).size())
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

int n;
string s;

const int MAX_BLOCKS = 400;

struct Block
{
    int a,b;
    int size() const { return b-a; }
};

Block blocks[2*MAX_BLOCKS];
Block newBlocks[2*MAX_BLOCKS];

int bs;
int nbs;

void rebuild()
{
    string newS = s;
    int j = 0;
    forn(bindex, bs)
        forsn(i, blocks[bindex].a, blocks[bindex].b)
            newS[j++] = s[i];
    s = newS;
    blocks[0] = {0, n};
    bs = 1;
}

void cutAndPaste(int a,int b)
{
    // cortar
    int pos = 0;
    nbs = 0;
    forn(bindex, bs)
    {
        Block block = blocks[bindex];
        bool containsA = pos < a && a < pos + block.size();
        bool containsB = pos < b && b < pos + block.size();
        int cutA = block.a + a-pos;
        int cutB = block.a + b-pos;
        if (containsA && containsB)
        {
            newBlocks[nbs++] = {block.a, cutA};
            newBlocks[nbs++] = {cutA, cutB};
            newBlocks[nbs++] = {cutB, block.b};
        }
        else if (containsA)
        {
            newBlocks[nbs++] = {block.a, cutA};
            newBlocks[nbs++] = {cutA, block.b};
        }
        else if (containsB)
        {
            newBlocks[nbs++] = {block.a, cutB};
            newBlocks[nbs++] = {cutB, block.b};
        }
        else
            newBlocks[nbs++] = block;
        pos += block.size();
    }
    // muevo
    bs = 0;
    pos = 0;
    forn(bindex, nbs)
    {
        if (a > pos || pos >= b)
            blocks[bs++] = newBlocks[bindex];
        pos += newBlocks[bindex].size();
    }
    pos = 0;
    forn(bindex, nbs)
    {
        if (a <= pos && pos < b)
            blocks[bs++] = newBlocks[bindex];
        pos += newBlocks[bindex].size();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q;
    cin >> n >> q;
    cin >> s;
    blocks[0] = {0, n};
    bs = 1;
    forn(query, q)
    {
        int a,b;
        cin >> a >> b;
        a--;
        
        cutAndPaste(a,b);
        
        if (bs > MAX_BLOCKS)
            rebuild();
    }
    rebuild();
    cout << s << "\n";
    return 0;
}
