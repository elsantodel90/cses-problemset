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

struct Event
{
    int delta;
    int time;
    bool operator<(const Event &o) const { return time < o.time; }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Event> events;
    events.reserve(2*n);
    forn(i,n)
    {
        int a,b;
        cin >> a >> b;
        events.push_back({1, a});
        events.push_back({-1, b});
    }
    sort(all(events));
    int total = 0;
    int best = 0;
    for (auto event : events)
    {
        total += event.delta;
        best = max(best, total);
    }
    cout << best << "\n";
    return 0;
}
