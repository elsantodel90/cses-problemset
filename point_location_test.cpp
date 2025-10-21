#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) cerr << #x << " = " << (x) << endl

#define SIZE(c) int((c).size())
#define ALL(c) begin(c),end(c)

typedef long long tint;

struct Point
{
    tint x,y;
    tint  operator % (const Point &o) const { return x*o.y - y*o.x; }
    Point operator - (const Point &o) const { return {x-o.x, y-o.y}; }
};

istream &operator>>(istream &is, Point &p)
{
    return is >> p.x >> p.y; 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int TT;
    cin >> TT;
    forn(tt,TT)
    {
        Point a,b,c;
        cin >> a >> b >> c;
        tint cross = (b-a)%(c-a);
        if (cross == 0)
            cout << "TOUCH\n";
        else if (cross > 0)
            cout << "LEFT\n";
        else
            cout << "RIGHT\n";
    }
    return 0;
}
