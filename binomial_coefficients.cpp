#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

typedef long long tint;

const int P = 1000000007;
const int MAXAB = 1000010;

int fact[MAXAB], invFact[MAXAB];

void precalc()
{
    fact[0] = 1;
    forsn(i,1,MAXAB)
        fact[i] = int((tint(fact[i-1]) * i) % P);
    invFact[0] = 1;
    invFact[1] = 1;
    forsn(i,2,MAXAB)
        invFact[i] = int((P-(invFact[P%i]*tint(P/i))%P)%P);
    forsn(i,1,MAXAB)
        invFact[i] = int((tint(invFact[i]) * invFact[i-1])%P);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precalc();
    int N; cin >> N;
    forn(i,N)
    {
        int a,b; 
        cin >> a >> b;
        tint ret = (((tint(fact[a]) * invFact[b]) % P) * invFact[a-b])%P;
        cout << ret << "\n";
    }
    return 0;
}
