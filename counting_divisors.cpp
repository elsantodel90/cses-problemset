#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_X = 1000010;

int divCount[MAX_X];

void precompute()
{
    for (int i=1;i<MAX_X;i++)
        for (int j=i;j<MAX_X;j+=i)
            divCount[j]++;
}

int main()
{
    precompute();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i=0;i<n;i++)
    {
        int x;
        cin >> x;
        cout << divCount[x] << "\n";
    }
    return 0;
}
