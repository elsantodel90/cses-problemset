#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>
#include <cassert>
#include <vector>
#include <list>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

struct BiStack
{
    list<int> chain[2];
    
    BiStack() {}
    BiStack(int x) {chain[0].push_back({x});}
    
    bool simple() const { return chain[0].empty() || chain[1].empty(); }
    int top(int index) const { return chain[index].empty() ? -1 : chain[index].back(); }
    int index(int x) const
    {
        if (top(0) == x) return 0; 
        if (top(1) == x) return 1;
        return -1;
    }
    bool empty() const { return chain[0].empty() && chain[1].empty(); }
};

void fail()
{
    cout << "IMPOSSIBLE\n";
    exit(0);
}

const int FREE = 0;
const int OPPOSITE = 1;
const int SAME = 2;

struct Assignment
{
    int assigned;
    int kind;
    int other;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<char> appeared(N, 0);
    vector<BiStack> stacks;
    vector<Assignment> assignments;
    vector<int> numbers;
    numbers.reserve(N);
    int nextX = 0;
    forn(steps,2*N)
    {
        if (!appeared[nextX])
        {
            int x;
            cin >> x;
            x--;
            numbers.push_back(x);
            appeared[x] = 1;
            stacks.push_back(BiStack(x));
        }
        else
        {
            int x = nextX++;
            dforn(i, SIZE(stacks))
            {
                int index = stacks[i].index(x);
                if (index >= 0)
                {
                    auto & xChain = stacks[i].chain[index];
                    auto & otherChain = stacks[i].chain[index^1];
                    forsn(j, i+1, SIZE(stacks))
                    {
                        if (!stacks[j].simple())
                            fail();
                        forn(si, 2)
                            otherChain.splice(otherChain.end(), stacks[j].chain[si]);
                    }
                    stacks.resize(i+1);
                    xChain.pop_back();
                    if (!otherChain.empty())
                        assignments.push_back({x, OPPOSITE, otherChain.back()});
                    else if (!xChain.empty())
                        assignments.push_back({x, SAME, xChain.back()});
                    else
                        assignments.push_back({x, FREE, 0});
                    if (stacks[i].empty())
                        stacks.pop_back();
                    goto noproblem;
                }
            }
            fail();
noproblem:;
        }
    }
    vector<int> ret(N);
    dforn(i, SIZE(assignments))
    {
        if (assignments[i].kind == SAME)
            ret[assignments[i].assigned] = ret[assignments[i].other];
        else if (assignments[i].kind == OPPOSITE)
            ret[assignments[i].assigned] = 3 - ret[assignments[i].other];
        else if (assignments[i].kind == FREE)
            ret[assignments[i].assigned] = 1;
        else
            assert(false);
    }
    forn(i,N)
    {
        if (i > 0)
            cout << " ";
        cout << ret[numbers[i]];
    }
    cout << "\n";
    return 0;
}
