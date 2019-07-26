#include <iostream>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TT; cin >> TT;
    forn(tt,TT)
    {
        int n; cin >> n;
        int x = 0;
        forn(i,n)
        {
            int val; cin >> val;
            x ^= val;
        }
        cout << (const char *[]){"first\n", "second\n"}[x == 0];
    }
    return 0;
}
