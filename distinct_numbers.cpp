#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 300000;

int v[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i=0;i<n;i++)
        cin >> v[i];
    sort(v, v+n);
    cout << unique(v,v+n)-v << "\n";
    return 0;
}
