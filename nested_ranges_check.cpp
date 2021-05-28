#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef pair<tint,tint> ptint;

struct Interval
{
    int start, end;
    
    int length() { return end-start; }
};

istream & operator>>(istream &is, Interval &inter)
{
    return is >> inter.start >> inter.end;
}

const int MAXN = 300000;

Interval intervals[MAXN];

struct Event
{
    int id;
    bool opens;
    
    int pos() const { return opens ? intervals[id].start : intervals[id].end; }
    
    int length() const { return intervals[id].length(); }
    
    bool operator<(const Event &o) const
    {
        return make_pair(pos(),length()) < make_pair(o.pos(),o.length());
    }
};

const int INF = 1000000000;

template <typename T>
ostream& operator<<(ostream &os, const vector<T> &v)
{
    forn(i,v.size())
    {
        if (i > 0)
            os << " ";
        os << v[i];
    }
    return os;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<Event> events;
    events.reserve(2*n);
    forn(i,n)
    {
        cin >> intervals[i];
        events.push_back({i,false});
        events.push_back({i,true});
    }
    sort(all(events));
    multiset<int> openStarts;
    int closedLastStart = -INF;
    vector<int> contains(n,0);
    vector<int> contained(n,0);
    for (Event e : events)
    {
        if (e.opens)
            openStarts.insert(e.pos());
        else // cierra
        {
            assert(openStarts.find(intervals[e.id].start) != openStarts.end());
            openStarts.erase(openStarts.find(intervals[e.id].start));
            if (!openStarts.empty())
                contained[e.id] |= *openStarts.begin() <= intervals[e.id].start;
            contains[e.id] |= closedLastStart >= intervals[e.id].start;
            closedLastStart = max(closedLastStart, intervals[e.id].start);
        }
    }
    cout << contains << "\n";
    cout << contained << "\n";
    
    return 0;
}
