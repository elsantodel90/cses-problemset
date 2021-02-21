#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <cassert>
#include <map>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define all(c) (c).begin(), (c).end()

typedef long long tint;

struct Movie
{
    int start, finish;
    bool operator<(const Movie &o) const { return finish < o.finish; }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Movie> v(n);
    forn(i,n)
        cin >> v[i].start >> v[i].finish;
    sort(all(v));    
    int total = 0;
    int now = 0;
    for (auto movie : v)
    if (now <= movie.start)
    {
        now = movie.finish;
        total++;
    }
        
    cout << total << "\n";
    return 0;
}
