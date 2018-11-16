#include <iostream>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAX = 1000000;

typedef long long tint;

int x[MAX], f[MAX], cycleNum[MAX];

int explore(int current, int num, int steppingOn)
{
    while (cycleNum[current] == steppingOn)
    {
        cycleNum[current] = num;
        current = f[current];
    }
    return current;
}

const int INF = 1000000000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    tint k; cin >> k;
    tint totalSum = 0;
    forn(i,n)
    {
        cin >> x[i];
        totalSum += x[i];
    }
    if (totalSum <= k)
        cout << "1" << endl;
    else
    {
        int j=0;
        tint currentSum = 0;
        forn(i,n)
        {
            while (currentSum + x[j] <= k)
            {
                currentSum += x[j];
                j = (j+1)%n;
            }
            assert(i != j);
            f[i] = j;
            currentSum -= x[i];
        }
        int nextCycle = 1;
        int ret = INF;
        forn(start, n)
        if (cycleNum[start] == 0)
        {
            int cycleStart = explore(start, nextCycle, 0);
            if (cycleNum[cycleStart] != nextCycle)
                explore(start, cycleNum[cycleStart], nextCycle);
            else
            {
                nextCycle++;
                // Encontramos un ciclo nuevo, y cycleStart pertenece
                int current = cycleStart;
                int cycleCost = 0;
                int movement = 0;
                do
                {
                    movement += (n + f[current] - current) % n;
                    current = f[current];
                    cycleCost++;
                } while (movement < n);
                ret = min(ret, cycleCost);
            }
        }
        cout << ret << endl;
    }
    return 0;
}
