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

struct Histograma
{
    map<int,int> h;
    
    void add(int x) { h[x]++; }
    void erase(int x) { assert(h[x] > 0); if (--h[x] == 0) h.erase(x); }
    int size() { return SIZE(h); }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,k;
    cin >> n >> k;
    
    vector<int> v(n);
    forn(i,n)
        cin >> v[i];
    
    // Mi ventana es [A,B)
    Histograma h;
    int B = 0;
    tint ret = 0;
    forn(A,n)
    {
        assert(A <= B);
        while (true)
        {
            if (B >= n) break;
            h.add(v[B]);
            if (h.size() > k)
            {
                h.erase(v[B]);
                break;
            }
            B++;
        }
        ret += B-A;
        h.erase(v[A]);
    }
    
    cout << ret << "\n";
    
    return 0;
}
