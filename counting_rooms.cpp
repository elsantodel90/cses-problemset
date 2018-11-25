#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

const int MAX = 2600;

string map[MAX];
bool visited[MAX][MAX];

const int dx[4] = {0,1,0,-1};
const int dy[4] = {-1,0,1,0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    map[0] = map[n+1] = string(m+2,'#');
    forn(i,n)
    {
        string row;
        cin >> row;
        map[i+1] = "#" + row + "#"; 
    }
    int totalRooms = 0;
    forn(i,n+2)
    forn(j,m+2)
    if (map[i][j] == '.' && !visited[i][j])
    {
        totalRooms++;
        vector<int> stack;
        #define put(x,y) {stack.push_back(x); stack.push_back(y); visited[x][y] = true; }
        put(i,j);
        while (!stack.empty())
        {
            int y = stack.back(); stack.pop_back();
            int x = stack.back(); stack.pop_back();
            forn(dir,4)
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (map[nx][ny] == '.' && !visited[nx][ny])
                    put(nx,ny);
            }
        }
    }
    cout << totalRooms << endl;
    return 0;
}
