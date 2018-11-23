#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

const int INF = 2000000000;
const int MAXN = 1000000;

int h[MAXN];

tint solve(int a, int b)
{
    if (b-a == 1)
        return h[a];
    else
    {
        int c = (a+b)/2;
        tint ret = max(solve(a,c), solve(c,b));
        int height = INF;
        int rangeStart = c, rangeEnd = c;
        forn(steps, b-a)
        {
            int newHeight;
            if (rangeEnd >= b || (rangeStart > a && h[rangeStart-1] > h[rangeEnd]))
            {
                newHeight = h[rangeStart-1];
                rangeStart--;
            }
            else
            {
                newHeight = h[rangeEnd];
                rangeEnd++;
            }
            height = min(height, newHeight);
            ret = max(ret, height * tint(rangeEnd-rangeStart));
        }
        return ret;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    forn(i,n)
        cin >> h[i];
    tint answer = solve(0,n);
    cout << answer << endl;
    return 0;
}
