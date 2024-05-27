#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

void print(const vector<int> &v)
{
    forn(i, SIZE(v))
    {
        if (i > 0)
            cout << " ";
        cout << v[i];
    }
    cout << "\n";
}

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

vector<int> piFunction(const string &s)
{
    vector<int> ret(SIZE(s)+1);
    ret[0] = -1;
    forsn(i,1, SIZE(s)+1)
    {
        int c = ret[i-1];
        while (c >= 0 && s[c] != s[i-1]) c = ret[c];
        ret[i] = c+1;
    }
    ret.erase(ret.begin());
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    print(zFunction(s));
    print(piFunction(s));
    return 0;
}
