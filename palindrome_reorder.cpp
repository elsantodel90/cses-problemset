#include <iostream>
#include <string>

using namespace std;

int h[32];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    for (char c : s)
        h[c-'A']++;
    int oddCount = 0;
    for (int x : h)
        oddCount += x % 2;
    if (oddCount > 1)
        cout << "NO SOLUTION\n";
    else
    {
        const int N = int(s.size());
        string out(N,0);
        for (int i=0; i<32;i++)
            if (h[i] % 2)
            {
                h[i]--;
                out[N/2] = char('A'+i);
                break;
            }
        int next = 0;
        for (int i=0; i<N/2;i++)
        {
            while (h[next] == 0) next++;
            out[i] = out[N-1-i] = char('A'+next);
            h[next] -= 2;
        }
        cout << out << "\n";
    }
}
