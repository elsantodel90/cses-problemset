#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define all(c) (c).begin(), (c).end()

typedef long long tint;

const tint INF = 1000000000000000LL;

vector<tint> sums[2] = {{0}, {0}};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    tint target;
    cin >> n >> target;
    forn(step,n)
    {
        tint x; cin >> x;
        vector<tint> &v = sums[step%2];
        int prevSize = int(v.size());
        forn(i, prevSize)
            v.push_back(v[i] + x);
    }
    vector<tint> &a = sums[0];
    vector<tint> &b = sums[1];
    a.push_back(INF);
    b.push_back(-INF);
    sort(all(a));
    sort(all(b));
    int i = 0, j = int(b.size())-1;
    tint ret = 0;
    while (i < int(a.size()-1) || j > 0)
    {
        tint s = a[i] + b[j];
        if (s < target)
            i++;
        else if (s > target)
            j--;
        else
        {
            int prevI = i, prevJ = j;
            while (a[i] == a[prevI]) i++;
            while (b[j] == b[prevJ]) j--;
            ret += tint(i-prevI) * tint(prevJ-j);
        }
    }
    cout << ret << "\n";
    return 0;
}
