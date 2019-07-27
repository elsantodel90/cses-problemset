#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a,b; cin >> n >> a >> b;
    tint maxSum = -1000000000000000LL;
    vector<tint> partialSum(n+1); 
    deque<int> nonDominated;
    partialSum[0] = 0;
    forn(i,n)
    {
        tint x; cin >> x;
        partialSum[i+1] = partialSum[i] + x;
        // Encontrar el minimo partialSum[x] para x del conjunto [i+1-b, i+1-a]
        int leavingIndex = i-b, enteringIndex = i+1-a;
        if (enteringIndex >= 0)
        {
            while (!nonDominated.empty() && partialSum[nonDominated.back()] >= partialSum[enteringIndex])
                nonDominated.pop_back();
            nonDominated.push_back(enteringIndex);
        }
        if (!nonDominated.empty() && nonDominated.front() == leavingIndex)
            nonDominated.pop_front();
        if (!nonDominated.empty())
            maxSum = max(maxSum, partialSum[i+1] - partialSum[nonDominated.front()]);
    }
    cout << maxSum << "\n";
    return 0;
}
