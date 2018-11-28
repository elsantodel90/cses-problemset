#include <iostream>
#include <cmath>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

typedef long long tint;

const tint P = 1000000007;

inline tint integerSum(tint n) { n%=P; return ((n*(n+1))/2)%P;}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    tint n;
    cin >> n;
    tint sum = 0;
    tint baseK = tint(sqrt(n));
    forsn(i,1,1+n/(baseK+1))
        sum = (sum + i * (n/i)) % P;
    forsn(k,1, baseK+1)
        sum = (sum + integerSum(n/k)) % P;
    sum = (sum + P - (baseK * integerSum(n/(baseK+1)))%P ) % P;
    cout << sum << endl;
    return 0;
}
