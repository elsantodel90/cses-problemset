#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define esta(x,c) ((c).find(x) != (c).end())

const int INF = 1000001000;

struct Element
{
    int value, index;
    bool operator <(const Element &other) const { return value < other.value;}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,x; cin >> n >> x;
    vector<Element> v(n+2);
    v[0].value = -INF;
    forn(i,n)
    {
        cin >> v[i+1].value;
        v[i+1].index = i+1;
    }
    v[n+1].value = INF;
    sort(v.begin(), v.end());
    int a = 1, b = n;
    forn(steps, 2*n)
    {
        int s = v[a].value + v[b].value;
        if (s < x)
            a++;
        else if (s > x)
            b--;
        else if (a != b)
        {
            cout << v[a].index << " " << v[b].index << "\n";
            return 0;
        }
        else if (v[a+1].value == v[a].value)
            a++;
        else
            b--;
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}
