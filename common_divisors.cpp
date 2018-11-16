#include <iostream>

using namespace std;

const int MAX = 1000100;

int cant[MAX];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x; cin >> x;
        cant[x]++;
    }
    for (int d = MAX; ; d--)
    {
        int s = 0;
        for (int i=d;i<MAX;i+=d)
            s += cant[i];
        if (s >= 2)
        {
            cout << d << endl;
            break;
        }
    }
    return 0;
}
