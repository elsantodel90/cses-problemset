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
    
    int N,Q;
    cin >> N >> Q;
    vector<tint> v(N);
    forn(i,N) cin >> v[i];
    vector<tint> prefix(N+1);
    prefix[0] = 0;
    forn(i,N)
        prefix[i+1] = v[i] + prefix[i];
    forn(i,Q)
    {
        int a,b;
        cin >> a >> b;
        a--;
        cout << (prefix[b] - prefix[a]) << "\n";
    }
	return 0;
}
