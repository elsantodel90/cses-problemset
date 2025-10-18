#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

#define ALL(c) begin(c), end(c)

typedef long long tint;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TT;
    cin >> TT;
    forn(tt,TT)
    {
        int n;
        cin >> n;
        bool allEven = true;
        forn(i,n)
        {
            int x;
            cin >> x;
            allEven &= x % 2 == 0;
        }
        if (allEven)
            cout << "second\n";
        else
            cout << "first\n";
    }
    return 0;
}
