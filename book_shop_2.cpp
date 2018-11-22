#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

const int MAXN = 1024;
const int MAX_X = 200000;

int hGeneric[MAXN], sGeneric[MAXN];
int h[MAXN], s[MAXN];
int dp[MAX_X];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,x;
    cin >> N >> x;
    forn(i,N)
        cin >> hGeneric[i];
    forn(i,N)
        cin >> sGeneric[i];
    int totalBooks = 0;
    forn(i,N)
    {
        int copies;
        cin >> copies;
        while (copies > 0)
        {
            int mult = (copies+1)/2;
            copies /= 2;
            h[totalBooks] = mult * hGeneric[i];
            s[totalBooks] = mult * sGeneric[i];
            totalBooks++;
        }
    }
    forn(i,totalBooks)
    dforsn(j, h[i] , x+1)
        dp[j] = max(dp[j], dp[j-h[i]] + s[i]);
    cout << *max_element(dp, dp+x+1) << endl;
    return 0;
}
