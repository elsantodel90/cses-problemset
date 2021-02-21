#include <iostream>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

typedef long long tint;

int v[32];

int n;

void f(int i)
{
    if (i == 0)
    {
        forn(j,n) cout << v[j];
        cout << "\n";
        return;
    }
    
    f(i-1);
    v[i-1] ^= 1;
    f(i-1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;

    f(n);
    
    return 0;
}
