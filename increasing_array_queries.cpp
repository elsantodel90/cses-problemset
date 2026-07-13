#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,abm,mmx,avx,tune=native")


#include <iostream>
#include <algorithm>

using namespace std;

#define forn(i,n) for(int i=0;i<(n);i++)
#define forsn(i,s,n) for(int i=(s);i<(n);i++)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << " ========================== " << endl

typedef long long tint;

const int MAXM = 210000;

const int BLOCK_SIZE = 450;
//const int BLOCK_SIZE = 6;

struct Query
{
    int index;
    int start, end;
    int blockId() const
    {
        return start/BLOCK_SIZE;
    }
    pair<int,int> key() const { return {blockId(), end}; }
    bool operator<(const Query &o) const
    {
        return key() < o.key();
    }
};

int x[MAXM];
tint answers[MAXM];

int v[MAXM];
tint p[MAXM];
Query queries[MAXM];


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N,Q;
    cin >> N >> Q;
    forn(i,N)
        cin >> x[i];
    while (N % BLOCK_SIZE != 0)
        x[N++] = 0;
    forn(i, Q)
    {
        queries[i].index = i;
        cin >> queries[i].start >> queries[i].end;
        queries[i].start--;
    }
    sort(queries, queries+Q);
    int nextQuery = 0;
    
    for (int check=BLOCK_SIZE; check <= N ; check += BLOCK_SIZE)
    {
        int blockId = check/BLOCK_SIZE - 1;
        DBG(blockId);
        // [check, j) es lo ya procesado por el greedy
        p[check] = 0;
        int hg = 0;
        tint costGreedy = 0;
        forsn(j, check, N+1)
        {
            while (nextQuery < Q && 
                   queries[nextQuery].blockId() == blockId &&
                   queries[nextQuery].end <= j)
            {
                //DBG(queries[nextQuery].index);
                int h=0;
                tint cost = 0;
                #define GREEDY_STEP(h, cost, i) do { \
                            h = max(h, x[i]); \
                            cost += h - x[i]; \
                        } while (false)
                forsn(i, queries[nextQuery].start, min(check, queries[nextQuery].end))
                    GREEDY_STEP(h,cost,i);
                if (queries[nextQuery].end < j)
                    answers[queries[nextQuery].index] = cost;
                else
                {
                    tint k = lower_bound(v+check,v+j, h) - v;
                    tint extra = (k-check) * h - p[k];
                    //DBG(h);
                    //DBG(k);
                    //DBG(cost);
                    //DBG(costGreedy);
                    //DBG(extra);
                    //RAYA;
                    answers[queries[nextQuery].index] = cost + costGreedy + extra;
                }
                nextQuery++;
            }
            // Agregar el elemento j al greedy
            GREEDY_STEP(hg,costGreedy,j);
            v[j] = hg;
            p[j+1] = p[j] + hg;
        }
    }
    
    forn(i,Q)
        cout << answers[i] << "\n";
    return 0;
}
