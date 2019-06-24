#include <iostream>

const int N = 7;

char board[N][N];

char pattern[N*N];
int total = 0;

int search[N][N];
int q[N*N];

void back(int x, int y, int pos)
{
    #define ok(x,y) (0 <= (x) && 0 <= (y) && (x) < N && (y) < N && !board[x][y])
    if (!ok(x,y)) return;
    if (pos == N*N-1)
    {
        total++;
        return;
    }
    if (x == 0 && y == N-1) return;
    if (ok(x-1,y) && ok(x+1,y) && !ok(x,y-1) && !ok(x,y+1)) return;
    if (!ok(x-1,y) && !ok(x+1,y) && ok(x,y-1) && ok(x,y+1)) return;
    board[x][y] = true;
    switch (pattern[pos])
    {
        case '?':
            back(x+1, y, pos+1);
            back(x, y+1, pos+1);
            back(x-1, y, pos+1);
            back(x, y-1, pos+1);
            break;
        case 'U':
            back(x, y-1, pos+1);
            break;
        case 'D':
            back(x, y+1, pos+1);
            break;
        case 'L':
            back(x-1, y, pos+1);
            break;
        case 'R':
            back(x+1, y, pos+1);
            break;
    }
    board[x][y] = false;
}

int main()
{
    std::cin >> pattern;
    back(0,0,0);
    std::cout << total << "\n";
    return 0;
}
