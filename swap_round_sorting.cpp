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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> v(n);
    forn(i,n)
    {
        cin >> v[i];
        v[i]--;
    }
    vector<vector<pair<int,int>>> rounds(2);
    vector<int> cycle;
    cycle.reserve(n);
    forn(i,n)
    if (v[i] >= 0)
    {
        cycle.clear();
        int x = i;
        while (v[x] >= 0)
        {
            cycle.push_back(x);
            int nx = v[x];
            v[x] = -1;
            x = nx;
        }
        forn(start, 2)
        forn(j, (SIZE(cycle)-start)/2)
            rounds[start].push_back({cycle[start+j], cycle[SIZE(cycle)-1-j]});
    }
    while (!rounds.empty() && rounds.back().empty())
        rounds.pop_back();
    cout << SIZE(rounds) << "\n";
    for (const auto &round : rounds)
    {
        cout << SIZE(round) << "\n";
        for (auto p : round)
            cout << p.first+1 << " " << p.second+1 << "\n";
    }
    return 0;
}
