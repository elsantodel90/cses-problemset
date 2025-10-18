#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 200000;

int ft[MAXN], v[MAXN];

void add(int x,int value)
{
    for(x++; x < MAXN; x += x&(-x))
        ft[x] += value;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    forn(i,n)
        cin >> v[i];
    int mp = 1;
    while (2*mp < n)
        mp *= 2;
    forn(i,n)
    {
        int index;
        cin >> index;
        index--;
        int x = 0, ac = 0;
        for (int p = mp; p > 0; p /= 2)
        {
            int nx = x|p;
            if (nx < n)
            {
                int q = ft[nx];
                int nac = ac+q;
                if (nx-nac <= index)
                {
                    ac = nac;
                    x = nx;
                }
            }
        }
        if (i > 0)
            cout << " ";
        cout << v[x];
        add(x,1);
    }
    cout << "\n";
    return 0;
}
