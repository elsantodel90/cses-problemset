#include <iostream>
#include <iomanip>
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

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define RAYA do {cerr << " =============================== " << endl; } while (false)

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<string> grid(N);
    forn(i,N)
        cin >> grid[i];
    vector<int> goodK = {0};
    vector<int> nextGoodK;
    forn(step, 2*N-1)
    {
        char minChar = 127;
        nextGoodK.clear();
        for (int k : goodK)
        {
            int i = step - k;
            int j = k;
            if (0 <= i && i < N && 0 <= j && j < N)
            {
                if (grid[i][j] < minChar)
                {
                    nextGoodK.clear();
                    minChar = grid[i][j];
                }
                if (grid[i][j] == minChar)
                    nextGoodK.push_back(k);
            }
        }
        assert(minChar < 127);
        cout << minChar;
        goodK.clear();
        int i = 0;
        forn(k, step+2)
        {
            while (i < SIZE(nextGoodK) && nextGoodK[i] < k-1)
                i++;
            if (i < SIZE(nextGoodK) && nextGoodK[i] <= k)
                goodK.push_back(k);
        }
    }
    cout << "\n";
    return 0;
}
