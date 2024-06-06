#include <iostream>

using namespace std;

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

typedef long long tint;

// ******************************
// Montgomery Transform
// 64 bit version: P < 2^62
//typedef unsigned long long ValueType; 
//const int VALUE_BITS = 64;
//typedef __uint128_t LargeType;
// 32 bit version: P < 2^30
typedef unsigned int ValueType;
const int VALUE_BITS = 32;
typedef unsigned long long LargeType;

const ValueType VALUE_MASK = ~ValueType(0);

template <typename T>
static T potlog(T a, unsigned long long b)
{
    T ret = T::ONE;
    while (b != 0)
    {
        if (b & 1) ret = ret * a;
        a = a*a;
        b >>= 1;
    }
    return ret;
}

template<ValueType PRIME_CONSTANT,
         ValueType MINUS_INV_P_MOD_2_64, 
         LargeType PLUS_2_128_MOD_P>
struct Montgomery
{
    static ValueType montReduce(LargeType value)
    {
        ValueType m = ValueType(value & VALUE_MASK);
        m *= MINUS_INV_P_MOD_2_64; // Convenient overflow
        return ValueType((value + LargeType(m)*PRIME_CONSTANT) >> VALUE_BITS);
    }

    static Montgomery montgomery(ValueType x)
    {
        return Montgomery(montReduce(PLUS_2_128_MOD_P * x));
    }

    static const Montgomery ONE;
    
    ValueType x;
    Montgomery() {x=0;}
    Montgomery operator+(const Montgomery &o) const
    {
        Montgomery ret = Montgomery(x+o.x);
        ret.x -= 2*PRIME_CONSTANT * (ret.x >= 2*PRIME_CONSTANT);
        return ret;
    }
    Montgomery operator-(const Montgomery &o) const
    {
        Montgomery ret = Montgomery(x-o.x);
        ret.x += 2*PRIME_CONSTANT * (x < o.x);
        return ret;
    }
    Montgomery operator*(const Montgomery &o) const
    {
        return Montgomery(montReduce(LargeType(x)*o.x));
    }
    ValueType recover() const
    {
        ValueType m = x * MINUS_INV_P_MOD_2_64; // Convenient overflow
        ValueType ret = ValueType((x + LargeType(m)*PRIME_CONSTANT) >> VALUE_BITS);
        if (ret >= PRIME_CONSTANT)
            ret -= PRIME_CONSTANT;
        return ret;
    }
    
    Montgomery inverse() const
    {
        return potlog(*this, PRIME_CONSTANT-2);
    }
    
    private:
        Montgomery(ValueType xx) {x=xx;}
};

typedef Montgomery<1000000007, 2226617417 , 582344008> Mod10_9_PLUS_7;
typedef Montgomery<1000000009, 737024967 , 688856453> Mod10_9_PLUS_9;

template<ValueType P, ValueType M1, LargeType M2>
const Montgomery<P, M1, M2>  Montgomery<P, M1, M2>::ONE = Montgomery<P, M1, M2>::montgomery(1);

// END Montgomery Transform
// ******************************


const int MAXN = 512;

Mod10_9_PLUS_7 dp[MAXN][MAXN];
Mod10_9_PLUS_7 binom[MAXN][MAXN];

void pascal()
{
    forn(n,MAXN)
    {
        binom[n][0] = binom[n][n] = Mod10_9_PLUS_7::ONE;
        forsn(k,1,n)
            binom[n][k] = binom[n-1][k-1] + binom[n-1][k];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pascal();
    string s; cin >> s;
    const int N = int(s.size());
    forn(i,N+1)
        dp[i][i] = Mod10_9_PLUS_7::ONE;
    forn(j,N+1)
    dforn(i,j)
    {
        Mod10_9_PLUS_7 &ret = dp[i][j] = Mod10_9_PLUS_7();
        forsn(k,i+1,j)
        if (s[i] == s[k])
            ret = ret + binom[(j-i)/2][(j-k-1)/2]*dp[i+1][k] * dp[k+1][j];
    }
    cout << dp[0][N].recover() << endl;
    return 0;
}
