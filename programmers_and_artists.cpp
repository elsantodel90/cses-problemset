#include <iostream>
#include <set>
#include <cassert>
 
using namespace std;
 
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
 
#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

typedef long long tint;

const int MAXN = 201000;

struct Person
{
    int skillA, skillB;
    int aMinusB() const { return skillA - skillB; }
    int bMinusA() const { return skillB - skillA; }
} v[MAXN];

#define COMPARATOR(name, field) struct name {bool operator()(int a, int b) const {return v[a].field != v[b].field ? v[a].field < v[b].field : a < b;}}

COMPARATOR(CmpA, skillA);
COMPARATOR(CmpB, skillB);
COMPARATOR(CmpBminusA, bMinusA());
COMPARATOR(CmpAminusB, aMinusB());

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a,b,n;
    cin >> a >> b >> n;
    forn(i,n)
        cin >> v[i].skillA >> v[i].skillB;
    set<int, CmpA> freeByA;
    set<int, CmpB> freeByB;
    set<int, CmpBminusA> aByBminusA;
    set<int, CmpAminusB> bByAminusB;
    forn(i,n)
    {
        freeByA.insert(i);
        freeByB.insert(i);
    }
    tint ret = 0;
    int usedA = 0, usedB = 0;
    forn(iterations, a+b)
    {
        int delta1 = 0, delta2 = 0, delta3 = 0, delta4 = 0;
        if (!freeByA.empty())
        {
            int bestA = v[*freeByA.rbegin()].skillA;
            if (usedA < a)
                delta1 = bestA;
            if (usedB < b && !aByBminusA.empty())
                delta3 = bestA + v[*aByBminusA.rbegin()].bMinusA();
        }
        if (!freeByB.empty())
        {
            int bestB = v[*freeByB.rbegin()].skillB;
            if (usedB < b)
                delta2 = bestB;
            if (usedA < a && !bByAminusB.empty())
                delta4 = bestB + v[*bByAminusB.rbegin()].aMinusB();
        }
        int bestDelta = max(max(delta1, delta2), max(delta3, delta4));
        assert(bestDelta > 0); // Input skills are positive, so having more people always helps, and a+b iterations should always be possible
        ret += bestDelta;
        #define MOVE_BEST_2(a,b,c) do {int id = *a.rbegin(); a.erase(id); b.erase(id); c.insert(id); } while (false)
        #define MOVE_BEST(a,b) do {int id = *a.rbegin(); a.erase(id); b.insert(id); } while (false)
        if (usedA < a && bestDelta == delta1)
        {
            MOVE_BEST_2(freeByA, freeByB, aByBminusA);
            usedA++;
        }
        else if (usedB < b && bestDelta == delta2)
        {
            MOVE_BEST_2(freeByB, freeByA, bByAminusB);
            usedB++;
        }
        else if (usedB < b && bestDelta == delta3)
        {
            MOVE_BEST(aByBminusA, bByAminusB);
            MOVE_BEST_2(freeByA, freeByB, aByBminusA);
            usedB++;
        }
        else if (usedA < a && bestDelta == delta4)
        {
            MOVE_BEST(bByAminusB, aByBminusA);
            MOVE_BEST_2(freeByB, freeByA, bByAminusB);
            usedA++;
        }
        else
            assert(false);
    }
    cout << ret << "\n";
    return 0;
}
