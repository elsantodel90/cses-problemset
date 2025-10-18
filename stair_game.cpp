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
        int heapXor = 0;
        forn(i,n)
        {
            int x;
            cin >> x;
            if (i % 2 == 1)
                heapXor ^= x;
        }
        if (heapXor == 0)
            cout << "second\n";
        else
            cout << "first\n";
    }
    return 0;
}
