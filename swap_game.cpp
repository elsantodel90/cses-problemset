#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define esta(x,c) ((c).find(x) != (c).end())

int powBase[9];

const int BASE = 10;
const int TARGET = 123456789;

const int SWAP_COUNT = 12;

const int swaps[SWAP_COUNT][2] = {
        {0,3},
        {1,4},
        {2,5},
        {3,6},
        {4,7},
        {5,8},
        
        {0,1},
        {1,2},
        {3,4},
        {4,5},
        {6,7},
        {7,8}
    };

struct Board
{
    int board;
    int dist;
    
    int swapped(int i, int j) const
    {
        int d1 = (board / powBase[i]) % BASE;
        int d2 = (board / powBase[j]) % BASE;
        return board - d1 * powBase[i] - d2 * powBase[j] 
                      + d2 * powBase[i] + d1 * powBase[j]; 
    }
    
    bool finished() const { return board == TARGET; }
};

namespace std {
    template <> struct hash<Board>
    {
        size_t operator()(const Board & board) const
        {
            return board.board;
        }
    };
};

const int MAX_STATES = 400000;

Board dist[MAX_STATES];
int totalBoards;

int index(int board)
{
    int a = 0, b = totalBoards;
    while (b-a > 1)
    {
        int c = (a+b)/2;
        if (dist[c].board <= board)
            a = c;
        else
            b = c;
    }
    return a;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    powBase[0] = 1;
    forn(i,8)
        powBase[i+1] = powBase[i] * BASE;
    
    totalBoards = 0;
    char boardString[16];
    forn(i,9)
        boardString[i] = char(i+1);
    do
    {
        int boardNumber = 0;
        forn(i,9)
            boardNumber = boardNumber * BASE + boardString[i];
        dist[totalBoards++] = {boardNumber, -1};
    } while (next_permutation(boardString, boardString + 9));
    
    int start = 0;
    forn(index,9)
    {
        int x;
        cin >> x;
        start = start * BASE + x;
    }
    int startIndex = index(start);
    dist[startIndex].dist = 0;
    queue<int> q;
    q.push(startIndex);
    while (!q.empty())
    {
        int currentIndex = q.front(); q.pop();
        Board current = dist[currentIndex];
        if (current.finished())
        {
            cout << current.dist << "\n";
            return 0;
        }
        forn(swapIndex, SWAP_COUNT)
        {
            int newIndex = index(current.swapped(swaps[swapIndex][0], swaps[swapIndex][1]));
            if (dist[newIndex].dist < 0)
            {
                dist[newIndex].dist = current.dist + 1;
                q.push(newIndex);
            }
        }
    }
    return 0;
}
