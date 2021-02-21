#include <iostream>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

typedef long long tint;

tint cantDigBloque(tint d, tint pot10)
{
    return 9LL * pot10 * d;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q; cin >> q;
    forn(queryNumber,q)
    {
        tint k; cin >> k;
        k--;
        
        tint d = 1;
        // Cant de numeros 9*10^(d-1)
        // Cant de digitos 9*10^(d-1) * d
        tint pot10 = 1;
        while (k >= cantDigBloque(d,pot10))
        {
            k -= cantDigBloque(d,pot10);
            
            d++;
            pot10 *= 10;
        }
        // Quiero el k-esimo de este bloque que miden d
        tint number = pot10 + k/d;
        cout << to_string(number)[k%d] << "\n";
    }
    
    return 0;
}
