#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

const int MAX = 2600;

string map[MAX];
int visited[MAX][MAX];
int pathDir[MAX][MAX];

const int dx[4] = {0,1,0,-1};
const int dy[4] = {-1,0,1,0};
inline int opuesta(int dir) { return dir ^ 2; }
inline char letter(int dir) { return "LDRU"[dir]; }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    map[0] = map[n+1] = string(m+2,'#');
    int startX=-1, startY=-1, endX=-1, endY=-1;
    forn(i,n)
    {
        string row;
        cin >> row;
        map[i+1] = "#" + row + "#";
        forn(k, map[i+1].size())
        {
            #define setPoint(px,py) {px = i+1; py = k; map[i+1][k] = '.';}
            if (map[i+1][k] == 'A') 
                setPoint(startX, startY);
            if (map[i+1][k] == 'B') 
                setPoint(endX, endY);
        }
    }
    queue<int> q;
    #define put(x,y, dir) {q.push(x); q.push(y); visited[x][y] = true; pathDir[x][y] = dir; }
    put(endX,endY, -1);
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        if (x == startX && y == startY)
        {
            cout << "YES" << endl;
            string path;
            while (x != endX || y != endY)
            {
                int nextDir = opuesta(pathDir[x][y]);
                path.push_back(letter(nextDir));
                x += dx[nextDir];
                y += dy[nextDir];
            }
            cout << path.size() << endl;
            cout << path << endl;
            return 0;
        } 
        forn(dir,4)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (map[nx][ny] == '.' && !visited[nx][ny])
                put(nx,ny, dir);
        }
    }
    cout << "NO" << endl;
    return 0;
}
