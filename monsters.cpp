#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define all(c) (c).begin(), (c).end()

typedef long long tint;

const int MAX = 1024;

const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};
const char* dirName = "RLDU";

int distAgus[MAX][MAX];
int distMonster[MAX][MAX];

string board[MAX];
int n,m;

const int INF = 1000000000;

void bfs(char start, int dist[MAX][MAX], int parent[MAX][MAX])
{
    #define METER(i,j,newDist, p) do { dist[i][j] = (newDist); q.push(i); q.push(j); parent[i][j] = p;} while (false)
    queue<int> q;
    forn(i,n)
    forn(j,m)
    if (board[i][j] == start)
        METER(i,j,0, -1);
    else
        dist[i][j] = INF;
    
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        int newDist = dist[x][y] + 1;
        forn(dir, 4)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (0 <= nx && nx < n && 0 <= ny && ny < m
                && board[nx][ny] != '#' && newDist < dist[nx][ny])
                METER(nx,ny,newDist, dir);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    forn(i,n)
        cin >> board[i];
    
    static int parent[MAX][MAX];
    
    bfs('M', distMonster, parent);
    bfs('A', distAgus, parent);
    
    forn(i,n)
    forn(j,m)
    if ((i == 0 || j == 0 || i == n-1 || j == m-1) && distAgus[i][j] < distMonster[i][j])
    {
        cout << "YES\n";
        int x = i;
        int y = j;
        string path;
        while (board[x][y] != 'A')
        {
            int d = parent[x][y];
            x -= dx[d];
            y -= dy[d];
            path.push_back(dirName[d]);
        }
        reverse(all(path));
        assert(distAgus[i][j] == int(path.size()));
        cout << path.size() << "\n";
        cout << path << "\n";
        return 0;
    }
    cout << "NO\n";
    return 0;
}
