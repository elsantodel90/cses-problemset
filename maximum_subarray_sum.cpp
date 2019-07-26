#include <iostream>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    tint maxSum = -1000000000000000LL;
    tint minPartial = 0;
    tint partialSum = 0;
    forn(i,n)
    {
        tint x; cin >> x;
        partialSum += x;
        maxSum = max(maxSum, partialSum - minPartial);
        minPartial = min(minPartial, partialSum);
    }
    cout << maxSum << "\n";
    return 0;
}
