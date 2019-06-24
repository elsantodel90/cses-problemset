#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

const int SIZE = 8;

char board[SIZE][SIZE];
int cover[SIZE][SIZE];

int total = 0;
int queens = 0;

const int dx[4] = {-1,-1,0 , 1};
const int dy[4] = { 0,-1,-1,-1};

void putqueen(int x, int y, int delta)
{
    queens += delta;
    forn(dir, 4)
    {
        int cx = x;
        int cy = y;
        while (0 <= cx && cx < SIZE && 0 <= cy && cy < SIZE)
        {
            cover[cx][cy] += delta; 
            cx += dx[dir];
            cy += dy[dir];
        }
    }
}

void back(int x, int y)
{
    if (x < 0)
    {
        x = SIZE-1;
        y--;
    }
    if (y < 0)
    {
        total += queens == SIZE;
        return;
    }
    back(x-1, y);
    if (cover[x][y] == 0 && board[x][y] == '.')
    {
        putqueen(x,y,1);
        back(x-1, y);
        putqueen(x,y,-1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    forn(i,SIZE)
    forn(j,SIZE)
        cin >> board[i][j];
    back(SIZE-1,SIZE-1);
    cout << total << "\n";
    return 0;
}
