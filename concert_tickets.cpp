#include <iostream>
#include <set>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,M;
    cin >> N >> M;
    multiset<int> s;
    forn(i,N)
    {
        int h;
        cin >> h;
        s.insert(h);
    }
    forn(i,M)
    {
        int t;
        cin >> t;
        auto it = s.upper_bound(t);
        if (it == s.begin())
            cout << "-1\n";
        else
        {
            --it;
            cout << *it << "\n";
            s.erase(it);
        }
    }
    return 0;
}
