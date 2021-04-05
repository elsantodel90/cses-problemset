#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    vector<int> pos(n+2);
    vector<int> v(n+2);
    pos[0] = v[0] = 0;
    pos[n+1] = v[n+1] = n+1;
    forsn(i,1,n+1)
    {
        cin >> v[i];
        pos[v[i]] = i;
    }
    int cfi = 1;
    forn(i,n+2-1)
        cfi += pos[i] > pos[i+1];

    #define SETPOS(x, np) do { cfi -= pos[x-1] > pos[x];\
                               cfi -= pos[x] > pos[x+1];\
                               pos[x] = np; \
                               cfi += pos[x-1] > pos[x];\
                               cfi += pos[x] > pos[x+1];\
                             } while (false)
        
    forn(operacion, m)
    {
        int a,b;
        cin >> a >> b;
        if (a != b)
        {
            int x = v[a], y = v[b];
            swap(v[a], v[b]);
            SETPOS(x, b);
            SETPOS(y, a);
        }
        cout << cfi << "\n";
    }
    return 0;
}
