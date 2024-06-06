#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cassert>
 
using namespace std;
 
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
 
#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

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

// ******************************
// FFT with Montgomery Transform


typedef unsigned int StackType; // Should be large enough to hold (INDEX_BITS + 1 + PLAN_BITS) bits
const int PLAN_BITS = 5;
const int MAX_PLAN = 1<<PLAN_BITS;
const int MAX_STACK = 5 * MAX_PLAN + 32; // probably 5 * (MAX_PLAN+1) should suffice
const int MAX_REMAINING = 9;
const int INDEX_BITS = 20; // Should be large enough to hold values [0,n] for actual FFT n

// FFT Values.
// ******************* About 61 bit integer convolutions.
//const int PRIME_POW_3 = 17;
//const int PRIME_POW_2 = 28;
//typedef Montgomery<4402556414938054657ULL, 12977410105451479039ULL , 3519512801902951630ULL> Value;
//const Value PRIME_ROOT = Value::montgomery(603);
//const Value ONE = Value::ONE;
// ******************* A pair of Montgomeries, to do Chinese Remainder Theorem in the end
// CRT will allow to recover non negative integers up to 7.47 * 10^17
const int PRIME_POW_3 = 4;
const int PRIME_POW_2 = 17;
const ValueType PRIME_1 = 902430721;
const ValueType PRIME_2 = 828112897;
const ValueType INVERSE_PRIME_2_MOD_PRIME_1 = 257837361;
const ValueType INVERSE_PRIME_1_MOD_PRIME_2 = 591509201;
typedef Montgomery<PRIME_1, 902430719 , 565472540> Mod1;
typedef Montgomery<PRIME_2, 828112895 , 535869581> Mod2;

struct Value
{
    Mod1 value1;
    Mod2 value2;
    static Value montgomery(ValueType a, ValueType b)
    {
        return {Mod1::montgomery(a), Mod2::montgomery(b)};
    }
    static Value montgomery(ValueType x)
    {
        return montgomery(x,x);
    }
    
    static const Value ONE;
    
    Value inverse() const
    {
        return {value1.inverse(), value2.inverse()};
    }
    
    LargeType recover() const
    {
        LargeType x1 = value1.recover();
        LargeType x2 = value2.recover();
        return (PRIME_2 * ((x1 * INVERSE_PRIME_2_MOD_PRIME_1)%PRIME_1) + 
                PRIME_1 * ((x2 * INVERSE_PRIME_1_MOD_PRIME_2)%PRIME_2)) % (LargeType(PRIME_1) * PRIME_2);
    }
    
    Value operator*(const Value &o) const
    {
        return {value1 * o.value1, value2 * o.value2};
    }
    
    Value operator+(const Value &o) const
    {
        return {value1 + o.value1, value2 + o.value2};
    }
};
    
const Value PRIME_ROOT = Value::montgomery(37, 38);

const Value Value::ONE = Value::montgomery(1);
 
const int NAIVE = 0;
const int SPLIT_3 = 2;
const int SPLIT_4 = 4;
 
struct PlanInfo
{
    int code;
    Value root, rootns;
    int tam;
};
 
#define SQUARED(x) ((x)*(x))
#define CUBED(x) ((x)*(x)*(x))
 
struct FFT
{
    int n;
    int levels;
    PlanInfo plan[MAX_PLAN];
    Value *v[2];
    
    FFT(int userN)
    {
        n = max(0, userN-1);
        int rem;
        int pow3,pow2;
        int lastRem;
        do
        {
            n++;
            levels = 0;
            lastRem = rem = n;
            pow3 = pow2 = 0;
            while (rem % 4 == 0)
            {
                if (rem > MAX_REMAINING)
                {
                    plan[levels++] = {SPLIT_4,Value(),Value(),rem};
                    lastRem = rem/4;
                }
                rem /= 4;
                pow2 += 2;
            }
            while (rem % 3 == 0)
            {
                if (rem > MAX_REMAINING)
                {
                    plan[levels++] = {SPLIT_3,Value(),Value(),rem};
                    lastRem = rem/3;
                }
                rem /= 3;
                pow3++;
            }
        } while (rem > 2 || pow2 > PRIME_POW_2 || pow3 > PRIME_POW_3);
        pow2 += (rem == 2);
        assert(pow2 <= PRIME_POW_2);
        assert(pow3 <= PRIME_POW_3);
        plan[levels++] = {NAIVE,Value(),Value(), lastRem};
        Value &root = plan[0].root = PRIME_ROOT;
        forn(i, PRIME_POW_2 - pow2)
            root = SQUARED(root);
        forn(i, PRIME_POW_3 - pow3)
            root = CUBED(root);
        forn(i, levels-1)
        if (plan[i].code == SPLIT_3)
        {
            plan[i+1].root = CUBED(plan[i].root);
            plan[i].rootns = potlog(plan[i].root, plan[i].tam / 3);
        }
        else if (plan[i].code == SPLIT_4)
        {
            plan[i+1].root = SQUARED(SQUARED(plan[i].root));
            plan[i].rootns = potlog(plan[i].root, plan[i].tam / 4);
        }
        else
            assert(false);
        v[0] = new Value[n];
        v[1] = new Value[n];
    }
    
    // Result is computed in v[1], v[0] is destroyed in the process.
    void fft()
    {
        static StackType stack[MAX_STACK];
        int stackTop = 0;
        stack[stackTop++] = 0; // level 0, start at 0, preprocess
        while (stackTop != 0)
        {
            StackType mask = stack[--stackTop];
            #define STACK_ITEM(s, pp, l) (StackType(s) | (StackType(pp)<<INDEX_BITS) | (StackType(l) << (INDEX_BITS+1)))
            int start = mask & ((StackType(1)<<INDEX_BITS)-1);
            int postProcess = (mask >> INDEX_BITS) & 1;
            int level = (mask >> (INDEX_BITS+1));
            Value *source = v[level&1] + start;
            Value *dest = v[1^(level&1)] + start;
            switch (plan[level].code + postProcess)
            {
                case SPLIT_4:
                    {
                        int ns = plan[level].tam>>2;
                        forn(i, ns)
                        {
                            dest[i] = source[4*i];
                            dest[ns+i] = source[4*i+1];
                            dest[2*ns+i] = source[4*i+2];
                            dest[3*ns+i] = source[4*i+3];
                        }
                        stack[stackTop++] = STACK_ITEM(start, 1, level);
                        stack[stackTop++] = STACK_ITEM(start, 0, level+1);
                        stack[stackTop++] = STACK_ITEM(start+ns, 0, level+1);
                        stack[stackTop++] = STACK_ITEM(start+2*ns, 0, level+1);
                        stack[stackTop++] = STACK_ITEM(start+3*ns, 0, level+1);
                    }
                    break;
                case SPLIT_4+1:
                    {
                        int ns = plan[level].tam/4;
                        Value x0 = Value::ONE;
                        Value x1 = plan[level].rootns;
                        Value x2 = x1*plan[level].rootns;
                        Value x3 = x2*plan[level].rootns;
                        forn(i, ns)
                        {
                            dest[i] = ((source[3*ns+i] * x0 + source[2*ns+i]) * x0 + source[ns+i]) * x0 + source[i];
                            dest[ns+i] = ((source[3*ns+i] * x1 + source[2*ns+i]) * x1 + source[ns+i]) * x1 + source[i];
                            dest[2*ns+i] = ((source[3*ns+i] * x2 + source[2*ns+i]) * x2 + source[ns+i]) * x2 + source[i];
                            dest[3*ns+i] = ((source[3*ns+i] * x3 + source[2*ns+i]) * x3 + source[ns+i]) * x3 + source[i];
                            x0 = x0 * plan[level].root;
                            x1 = x1 * plan[level].root;
                            x2 = x2 * plan[level].root;
                            x3 = x3 * plan[level].root;
                        }
                    }
                    break;
                case SPLIT_3:
                    {
                        int ns = plan[level].tam/3;
                        forn(i, ns)
                        {
                            dest[i] = source[3*i];
                            dest[ns+i] = source[3*i+1];
                            dest[2*ns+i] = source[3*i+2];
                        }
                        stack[stackTop++] = STACK_ITEM(start, 1, level);
                        stack[stackTop++] = STACK_ITEM(start, 0, level+1);
                        stack[stackTop++] = STACK_ITEM(start+ns, 0, level+1);
                        stack[stackTop++] = STACK_ITEM(start+2*ns, 0, level+1);
                    }
                    break;
                case SPLIT_3+1:
                    {
                        int ns = plan[level].tam/3;
                        Value x0 = Value::ONE;
                        Value x1 = plan[level].rootns;
                        Value x2 = x1*plan[level].rootns;
                        forn(i, ns)
                        {
                            dest[i] = (source[2*ns+i] * x0 + source[ns+i]) * x0 + source[i];
                            dest[ns+i] = (source[2*ns+i] * x1 + source[ns+i]) * x1 + source[i];
                            dest[2*ns+i] = (source[2*ns+i] * x2 + source[ns+i]) * x2 + source[i];
                            x0 = x0 * plan[level].root;
                            x1 = x1 * plan[level].root;
                            x2 = x2 * plan[level].root;
                        }
                    }
                    break;
                case NAIVE:
                    {
                        Value x = Value::ONE;
                        forn(i, plan[level].tam)
                        {
                            dest[i] = source[plan[level].tam-1];
                            dforn(j, plan[level].tam-1)
                                dest[i] = dest[i] * x + source[j];
                            x = x * plan[level].root;
                        }
                    }
                    break;
                default:
                    while (true); // Cannot happen: trigger undefined behavior for optimizer
            }
        }
    }

    // Usually not needed in competitive programming,
    // as it is faster to just leak the memory, and when doing a single
    // large fft, max memory usage is the same.
    //~FFT() { free(v[0]); free(v[1]); }
};
 
Value *convolucion(const ValueType* v1, int n1, const ValueType* v2, int n2)
{
    int s = n1 + n2 - 1;
    FFT fft1(s), fft2(s);
    forn(i, n1)
        fft1.v[0][i] = Value::montgomery(v1[i]);
    fft1.fft();
    forn(i, n2)
        fft2.v[0][i] = Value::montgomery(v2[i]);
    fft2.fft();
    forn(i,fft2.n)
        fft2.v[0][fft2.n-1-i] = fft2.v[1][i] * fft1.v[1][i];
    fft2.fft();
    Value x = Value::ONE;
    Value invN = Value::montgomery(fft2.n).inverse();
    forn(i, fft2.n)
    {
        fft2.v[1][i] = fft2.v[1][i] * invN * x;
        x = x * fft2.plan[0].root;
    }
    return fft2.v[1];
}
 
Value *convolucion(const vector<ValueType> &v1, const vector<ValueType> &v2)
{
    return convolucion(v1.data(), SIZE(v1), v2.data(), SIZE(v2));
}
 
// END FFT with Montgomery Transform
// ******************************

 
 
 
 
 
 
 
 
typedef long long tint;
typedef tint tipo; // o int
 
const int MAXN = 210000;
 
ValueType v[MAXN];
ValueType vRev[MAXN];
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int k = 0;
    v[k] = 1;
    for (char c : s)
    {
        if (c == '0')
            v[k]++;
        else if (c == '1')
            v[++k] = 1;
        else
            assert(false);
    }
    int ones = k;
    k++;
    tint ret0 = 0;
    forn(i,k)
        ret0 += tint(v[i]) * (v[i]-1);
    ret0 /= 2;
    cout << ret0;
    forn(i,k)
        vRev[k-1-i] = v[i];
    Value *ret = convolucion(v, k, vRev, k);
    forsn(i,ones+1, ones+1+ones)
        cout << " " << ret[i].recover();
    forn(i, SIZE(s)+1-k)
        cout << " 0";
    cout << "\n";
    return 0;
}
