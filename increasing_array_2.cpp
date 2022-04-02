#include <iostream>
#include <set>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    tint s = 0;
    multiset<int> m;
    forn(i,N)
    {
        int x;
        cin >> x;
        s += x;
        m.insert(x);
        m.insert(x);
        m.erase(prev(m.end()));
    }
    for (int x : m)
        s -= x;
    cout << s << "\n";
    return 0;
}
