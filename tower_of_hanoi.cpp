#include <iostream>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

typedef long long tint;

// Mover n discos, de a hasta b usando c como pila intermedia
void f(int n, int a, int b, int c)
{
    if (n > 0)
    {
        f(n-1, a, c, b);
        cout << a << " " << b << "\n";
        f(n-1, c, b, a);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    cout << (1<<n)-1 << "\n";
    f(n, 1, 3, 2);
    
    return 0;
}
