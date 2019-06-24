#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

#define all(s) (s).begin(), (s).end()

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    sort(all(s));
    vector<string> allPermutations;
    do
    {
        allPermutations.push_back(s);
    } while (next_permutation(all(s)));
    cout << allPermutations.size() << "\n";
    for (const string &p : allPermutations)
        cout << p << "\n";
    return 0;
}
