#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const char * message[2] = {"NO\n","YES\n"};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    forn(query,t)
    {
        int A,B; cin >> A >> B;
        int s = (A+B)/3;
        cout << message[3*s == A+B && A >= s && B >= s];
    }
    return 0;
}
