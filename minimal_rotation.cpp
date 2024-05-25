#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define DBG(x) cerr << #x << " = " << (x) << endl

using tint = long long;

const int BASE = 26;
const int MOD = 1182684443;

struct Hash
{
    int value;
    void addRight(char c)
    {
        value = int((tint(value) * BASE + (c-'a')) % MOD);
    }
    void multiply(const Hash &o)
    {
        value = int((tint(value) * o.value) % MOD);
    }
    
    void subtract(const Hash &o)
    {
        value -= o.value;
        if (value < 0)
            value += MOD;
    }
    
    bool operator==(const Hash &o) const
    {
        return value == o.value;
    }
};

const int MAXN = 1000100;

Hash powBase[MAXN];

char s[MAXN];
Hash h[2*MAXN];
int N;

void hashInit()
{
    powBase[0] = {1};
    forn(i,N)
    {
        powBase[i+1] = powBase[i];
        powBase[i+1].multiply({BASE});
    }
    h[0] = {0};
    forsn(i, 1, 2*N+1)
    {
        h[i] = h[i-1];
        h[i].addRight(s[(i-1)%N]);
    }
}

Hash substringHash(int i, int j)
{
    Hash ret = h[j];
    Hash left = h[i];
    left.multiply(powBase[j-i]);
    ret.subtract(left);
    return ret;
}

bool rotLower(int i, int j)
{
    int a = 0, b = N+1;
    while (b-a > 1)
    {
        int c = (a+b)/2;
        if (substringHash(i, i+c) == substringHash(j, j+c))
            a = c;
        else
            b = c;
    }
    return s[(i+a)%N] < s[(j+a)%N];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    N = int(strlen(s));
    hashInit();
    
    int bestRot = 0;
    forsn(i, 1, N)
    if (rotLower(i, bestRot))
        bestRot = i;
    cout << s + bestRot;
    s[bestRot] = 0;
    cout << s << "\n";
    return 0;
}
