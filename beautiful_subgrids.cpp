#pragma GCC target ("sse4.2")

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
 
using namespace     std;
 
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
 
const int MAXN = 3000;
const int WORD_SIZE = 64;
 
typedef unsigned long long Word;
typedef long long tint;
 
const int LEN = 1 + MAXN/WORD_SIZE;
 
Word a[MAXN][LEN];
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    forn(i, n)
    {
        string s; cin >> s;
        forn(j,n)
            a[i][j/WORD_SIZE] |= Word(s[j] != '0')<<(j%WORD_SIZE);
    }
 
    tint ans = 0;
 
 
    forn(r1, n){
        forsn(r2, r1+1, n){
            int cnt = 0;
            forn(i,LEN)
                cnt += __builtin_popcountll(a[r1][i] & a[r2][i]);
            ans += cnt*(cnt-1)/2;
        }
    }
 
    cout << ans << "\n";
    
    return 0;
}
