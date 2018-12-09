#include <iostream>
#include <set>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x,n; cin >> x >> n;
    set<int> lights{0,x};
    multiset<int> gaps{x};
    forn(i,n)
    {
        int p; cin >> p;
        auto it = lights.lower_bound(p);
        int previous = *prev(it);
        int next = *it;
        lights.insert(p);
        gaps.erase(gaps.find(next-previous));
        gaps.insert(p-previous);
        gaps.insert(next-p);
        if (i > 0 )
            cout << " ";
        cout << *gaps.rbegin();
    }
    cout << "\n";
    return 0;
}
