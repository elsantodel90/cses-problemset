#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

const int MAXN = 1001000;
const int MAX_ASCII = 128;

int jumps[MAXN];
int cant[MAX_ASCII];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    const int N = int(s.size());
    for (char c : s)
        cant[int(c)+1]++;
    forsn(i,1,MAX_ASCII)
        cant[i] += cant[i-1];
    forn(i,N)
        jumps[cant[int(s[i])]++] = i;
    int current = jumps[0];
    assert(s[current] == '#');
    string ret(N-1,'$');
    forn(i,N-1)
    {
        current = jumps[current];
        ret[i] = s[current];
    }
    cout << ret << endl;
    return 0;
}
