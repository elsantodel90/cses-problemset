#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>
#include <cassert>
#include <vector>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define DBG(x) do {cerr << #x << " = " << (x) << endl;} while (false)
#define DBGY(x) do {cerr << #x << " = " << (x) << " , ";} while (false)
#define DBG2(x,y) do {DBGY(x); DBG(y); } while (false)
#define DBG3(x,y,z) do {DBGY(x); DBGY(y); DBG(z); } while (false)
#define DBG4(x,y,z,w) do {DBGY(x); DBGY(y); DBGY(z); DBG(w); } while (false)
#define RAYA do {cerr << " ================ " << endl; } while (false)

#define SIZE(c) int((c).size())
#define esta(x,c) ((c).find(x) != (c).end())
#define all(c) (c).begin(), (c).end()

typedef long long tint;
typedef pair<int,int> pint;
typedef vector<int> vint;
typedef pair<tint,tint> ptint;

template <typename T>
ostream & operator <<(ostream &os, const vector<T>& v) {
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os;
}

template <typename T>
istream & operator >>(istream &is, vector<T>& v) {
    int n;
    is >> n;
    v.resize(n);
    forn(i,n)
        is >> v[i];
    return is;
}

                
/*                
Procedimiento para resolver luego de computados los padres/antipadres: (si falla, decir imposible)
EN ORDEN:
    0) Si hay N en el output, ganamos
    1) Si el siguiente esta en stack, mandarlo.
    2) Si no hay mas input, perdimos 
    3) Si no, si el siguiente no tiene padre/antipadre, jugar goloso [poner X en la mas chica, que sea mayor a X]
        [Si no se puede, perdimos]
    4) Si no, poner en la opuesta al antipadre / la misma del padre
*/

const int INF = 1000000000;

bool solve(int N, const vector<int> &parent, const vector<int> &antiParent, const vector<int> &v)
{
    vector<int> ret(N, -1);
    vector<int> stacks[2];
    forn(k,2) stacks[k].push_back(INF);
    int sent = 0;
    int i = 0;
    while (sent < N)
    {
        forn(k,2)
        if (stacks[k].back() == sent)
        {
            stacks[k].pop_back();
            sent++;
            goto nextIteration;
        }
        {
            if (i >= N)
                return false;
            int k = 0;
            if (parent[i] >= 0)
            {
                assert(ret[parent[i]] >= 0);
                k = ret[parent[i]];
            }
            else if (antiParent[i] >= 0)
            {
                assert(ret[antiParent[i]] >= 0);
                k = ret[antiParent[i]] ^ 1;
            }
            else if (stacks[0].back() > v[i] && !(stacks[1].back() > v[i] && stacks[1].back() < stacks[0].back()))
                k = 0;
            else
                k = 1;
            ret[i] = k;
            stacks[k].push_back(v[i]);
            i++;
        }
nextIteration:;
    }
    for (int &x : ret)
        x++;
    cout << ret << "\n";
    return true;
}

struct Restriction
{
    int lowerBound;
    int anti;
    
    bool operator<(const Restriction &o) const
    {
        if (lowerBound != o.lowerBound)
            return lowerBound < o.lowerBound;
        return anti < o.anti;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<int> v(N);
    forn(i,N)
        cin >> v[i];
    for (int &x : v)
        x--;
    
    vector<int> pos(N+1,-1);
    vector<int> parent(N,-1), antiParent(N,-1);
    vector<vector<Restriction>> turnOn(N);
    vector<vector<Restriction>> turnOff(N);
    int following = 0;
    forn(i,N)
    {
        int x = v[i];
        pos[x] = i;
        if (x == following)
        {
            following = x+1;
            while (pos[following] >= 0)
                following++;
            
            /* 
             * Restricciones que genera el x que a su derecha el primero es following (con x < following)
                Si following=x+1, nada
                Si no:
                    A y B se pueden buscar "a lo bruto", en O(following-x)
                    Sea A el primer X con x < X < following (ta a la izquierda de x y existe)
                    Sea B el ultimo X con X > following a la izquierda de x, si existe (si no, no hay restricciones)
                        1) Todos los >following entre A y B (incluido B) van en la opuesta que A
                        
                        2) Todos los x < X < following entre A y B (no incluido A) van en la misma que A
                            [Se pueden bruteforcear los valores de X y marcar]
            */
            
            int A = N;
            forsn(val, x+1, following)
                A = min(A, pos[val]);
            if (A < N)
            {
                assert(0 <= A);
                assert(A < i);
                int B = -1;
                dforn(j, i)
                if (v[j] > following)
                {
                    B = j;
                    break;
                }
                if (B >= A)
                {
                    assert(B > A);
                    forsn(val, x+1, following)
                    if (A < pos[val] && pos[val] < B)
                        parent[pos[val]] = A;
                    turnOn[A].push_back({following, A});
                    turnOff[B+1].push_back({following, A});
                }
            }
            else
                assert(following == x+1);
        }
    }
    multiset<Restriction> restrictions;
    forn(i,N)
    {
        for (Restriction r : turnOn[i])
            restrictions.insert(r);
        for (Restriction r : turnOff[i])
            restrictions.erase(restrictions.find(r));
        if (!restrictions.empty())
        {
            Restriction r = *restrictions.begin();
            if (v[i] > r.lowerBound)
                antiParent[i] = r.anti;
        }
    }
    forn(i,N)
    {
        DBG(i);
        DBG(v[i]);
        DBG(parent[i]);
        DBG(antiParent[i]);
        RAYA;
    }
    
    if (!solve(N, parent, antiParent, v))
        cout << "IMPOSSIBLE\n";
    
    return 0;
}
