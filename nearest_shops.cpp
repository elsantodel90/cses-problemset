#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=(n)-1;i>=(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long tint;

struct Event
{
    int shop;
    int dist;
};

struct QueueEvent
{
    Event e;
    int city;
};

const int NEAREST_COUNT = 2; 

queue<QueueEvent> q;

struct NodeStatus
{
    Event events[NEAREST_COUNT];
    bool visited(int shop) const
    {
        forn(k,NEAREST_COUNT)
        if (events[k].shop == shop)
            return true;
        return false;
    }
    int nextIndex() const
    {
        int ret = 0;
        forn(k,NEAREST_COUNT)
            ret += events[k].shop >= 0;
        return ret;
    }
    void push(int city, const Event &e)
    {
        if (visited(e.shop))
            return;
        int index = nextIndex();
        if (index < NEAREST_COUNT)
        {
            events[index] = e;
            q.push({e, city});
        }
    }
};

const int MAXN = 150000;
NodeStatus status[MAXN];

vector<int> g[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    cin >> n >> m;
    forn(i,n)
    forn(k,NEAREST_COUNT)
        status[i].events[k].shop = -1, status[i].events[k].dist = -1;
    int k;
    cin >> k;
    forn(i,k)
    {
        int s;
        cin >> s;
        s--;
        status[s].push(s, {s, 0});
    }
    forn(i,m)
    {
        int x,y;
        cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    while (!q.empty())
    {
        QueueEvent e = q.front(); q.pop();
        Event newEvent = e.e;
        newEvent.dist++;
        for (int y : g[e.city])
            status[y].push(y, newEvent);
    }
    forn(i,n)
    {
        int dist = status[i].events[0].dist;
        if (dist == 0)
            dist = status[i].events[1].dist;
        if (i > 0)
            cout << " ";
        cout << dist;
    }
    cout << "\n";
    return 0;
}
