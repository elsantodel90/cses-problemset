#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    vector<int> border(SIZE(s)+1);
    border[0] = -1;
    forsn(i,1, SIZE(s)+1)
    {
        int c = border[i-1];
        while (c >= 0 && s[c] != s[i-1]) c = border[c];
        border[i] = c+1;
    }
    // Just for fun, a needlessly complicated exercise:
    // iterate and "flip" the border arrows, 
    // exactly as in the coding exercise of reversing a
    // forward-linked list in a single traversal.
    int x = SIZE(s);
    int aux = border[x];
    while (x > 0)
    {
        int sig = aux;
        aux = border[sig];
        border[sig] = x;
        x = sig;
    }
    // After that, just iterate forward and print.
    bool pri = true;
    while (border[x] < SIZE(s))
    {
        if (pri)
            pri = false;
        else
            cout << " ";
        cout << border[x];
        x = border[x];
    }
    cout << "\n";
    return 0;
}
