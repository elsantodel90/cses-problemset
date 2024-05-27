#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

vector<int> zFunction(const string &s)
{
    vector<int> z(SIZE(s), 0);
    int A = 0, B = 0;
    forsn(i, 1, SIZE(s))
    {
        if (B > i)
            z[i] = min(z[i-A], B-i);
        while (i+z[i] < SIZE(s) && s[i+z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > B)
        {
            A = i;
            B = i + z[i];
        }
    }
    return z;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, pat;
    cin >> s >> pat;
    vector<int> z = zFunction(pat+s);
    int ret = 0;
    forn(i, SIZE(s))
        ret += z[SIZE(pat)+i] >= SIZE(pat);
    cout << ret << "\n";
    return 0;
}
