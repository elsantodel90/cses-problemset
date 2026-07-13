#pragma GCC target ("sse4.2")
#include <iostream>
#include <vector>
#include <bitset>
 
using namespace std;
 
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
 
const int MAXN = 3000;
 
bitset<MAXN> a[MAXN];
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    forn(i, n) cin >> a[i];
 
    long long ans = 0;
 
 
    forn(r1, n){
        forsn(r2, r1+1, n){
            int cnt = int((a[r1]&a[r2]).count());
            ans += cnt*(cnt-1)/2;
        }
    }
 
    cout << ans << "\n";
    
    return 0;
}
