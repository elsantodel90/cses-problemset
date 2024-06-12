#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>
#include <cassert>
#include <vector>
#include <list>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

int histogram[32];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    for (char c : s)
        histogram[c-'A']++;
    int n = SIZE(s);
    int lastLetter = -1;
    forn(i,n)
    {
        int maxLetter = 0;
        forn(j,26)
            maxLetter = max(maxLetter, histogram[j]);
        int total = n-i;
        forn(j, 26)
        if (histogram[j] > 0 && j != lastLetter && (histogram[j] == maxLetter || 2*maxLetter <= total))
        {
            histogram[j]--;
            s[i] = char('A' + j);
            lastLetter = j;
            goto nextLetter;
        }
        cout << "-1\n";
        return 0;
nextLetter:;
    }
    cout << s << "\n";
    return 0;
}
