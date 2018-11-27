#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

typedef long long tint;

const int MAXN = 250000;
const int MAX_EVENTS = 2*MAXN;

struct Event
{
    int index, day;
    bool opens;
    bool operator <(const Event &o) const { return (day != o.day) ? (day < o.day) : (opens > o.opens); } 
} events[MAX_EVENTS];

int answer[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    forn(i,N)
    {
        int a,b;
        cin >> a >> b;
        events[2*i] = {i, a, true};
        events[2*i+1] = {i, b, false};
    }
    sort(events, events+2*N);
    vector<int> availableColors;
    int totalColors = 0;
    forn(eventIndex, 2*N)
    {
        Event e = events[eventIndex];
        if (e.opens)
        {
            if (availableColors.empty())
                availableColors.push_back(++totalColors);
            answer[e.index] = availableColors.back();
            availableColors.pop_back();
        }
        else
            availableColors.push_back(answer[e.index]);
    }
    
    cout << totalColors << "\n";
    forn(i,N)
    {
        if (i>0) cout << " ";
        cout << answer[i];
    }
    cout << "\n";
    return 0;
}
