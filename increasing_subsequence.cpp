#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 1000000;

int v[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int ret = 0;
    forn(i,n)
    {
        int x; cin >> x;
        int a = -1, b = ret;
        while (b-a > 1)
        {
            int c = (a+b)/2;
            if (v[c] >= x)
                b = c;
            else
                a = c;
        }
        if (b == ret)
            ret++;
        v[b] = x;
    }
    cout << ret << endl;
    return 0;
}
