#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

#define ALL(c) begin(c), end(c)

typedef unsigned long long tint;

const int MAX = 10000000;
pair<int,int> isTwoSquare[MAX+1];
const pair<int,int> ZERO{0,0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int a = 0; a*a <= MAX; a++)
    for (int b = 0; b <= a; b++)
    {
        int s = a*a+b*b;
        if (s > MAX)
            break;
        isTwoSquare[s] = {a,b};
    }
    int TT;
    cin >> TT;
    forn(tt,TT)
    {
        int n;
        cin >> n;
        if (n == 0)
            cout << "0 0 0 0\n";
        else if (isTwoSquare[n] != ZERO)
            cout << "0 0 " << isTwoSquare[n].first << " " << isTwoSquare[n].second << "\n";
        else
        {
            int s = 1;
            while (isTwoSquare[s] == ZERO || isTwoSquare[n-s] == ZERO)
                s++;
            cout << isTwoSquare[s].first << " " <<
                    isTwoSquare[s].second << " " <<
                    isTwoSquare[n-s].first << " " <<
                    isTwoSquare[n-s].second << "\n";
        }
    }
    return 0;
}
