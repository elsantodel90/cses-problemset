#include <iostream>
#include <set>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    multiset<int> towers;
    forn(i,N)
    {
        int cube;
        cin >> cube;
        auto it = towers.upper_bound(cube);
        if (it == towers.end())
            towers.insert(cube);
        else
        {
            towers.erase(it);
            towers.insert(cube);
        }
    }
    cout << towers.size() << endl;
    return 0;
}
