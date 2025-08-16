#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

const int dx[8] = {1,2,1,2,-1,-2,-1,-2};
const int dy[8] = {2,1,-2,-1,2,1,-2,-1};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> d(n, vector<int>(n, -1));
    queue<int> q;
    #define PUSH(x,y,dist) do { q.push(x); q.push(y); d[x][y] = dist; } while (false)
    PUSH(0,0,0);
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        int newDist = d[x][y]+1;
        forn(dir, 8)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (0 <= nx && nx < n &&
                0 <= ny && ny < n && d[nx][ny] < 0)
                PUSH(nx,ny,newDist);
        }
    }
    
    forn(i,n)
    {
        forn(j,n)
        {
            if (j > 0)
                cout << " ";
            cout << d[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}
