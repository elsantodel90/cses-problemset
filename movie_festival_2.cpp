#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

#define all(c) (c).begin(), (c).end()

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k; cin >> n >> k;
    struct Event
    {
        int pos, interval;
        bool opens;
        bool operator <(const Event &other) const
        {
            if (pos != other.pos)
                return pos < other.pos;
            return opens < other.opens;
        }
    };
    struct Interval { int start, finish; };
    vector<Interval> v;
    vector<Event> events;
    int ret = 0;
    forn(i,n)
    {
        Interval inter;
        cin >> inter.start >> inter.finish;
        v.push_back(inter);
        if (inter.start == inter.finish)
            ret++;
        else
        {
            events.push_back({inter.start , i, true});
            events.push_back({inter.finish, i, false});
        }
    }
    sort(all(events));
    multiset<int> usedIntervalsFinish;
    for (Event e : events)
        if (e.opens)
        {
            usedIntervalsFinish.insert(v[e.interval].finish);
            if (int(usedIntervalsFinish.size()) > k)
                usedIntervalsFinish.erase(prev(usedIntervalsFinish.end()));
        }
        else if (!usedIntervalsFinish.empty() && *usedIntervalsFinish.begin() == e.pos)
        {
            ret++;
            usedIntervalsFinish.erase(usedIntervalsFinish.begin());
        }
    cout << ret << "\n";
    return 0;
}
