#include <iostream>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)

const int MAXN = 1000000;

int deg[MAXN]; // De hecho es "grado menos uno"
int code[MAXN];
int nextCandidateLeaf = 1;
int nextLeaf = -1;

// Ejemplo de la mas o menos conocida "cola de prioridad O(1) amortizado" asumiendo:
//        Se puede crear un arreglo de longitud "maximo numero posible" (como counting sort)
//        A lo sumo una insercion por debajo del "nextCandidate" entre iteraciones (asi ese se va inmediatamente y no "rompe" al candidato)

int findNextLeaf()
{
    if (nextLeaf >= 0)
    {
        int ret = nextLeaf;
        nextLeaf = -1;
        return ret;
    }
    else
    {
        while (deg[nextCandidateLeaf] > 0)
            nextCandidateLeaf++;
        return nextCandidateLeaf++;
    }
}

void addLeaf(int x)
{
    if (x < nextCandidateLeaf)
        nextLeaf = x;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    forn(i,N-2)
    {
        cin >> code[i];
        deg[code[i]]++;
    }
    code[N-2] = N;
    forn(i,N-1)
    {
        int leaf = findNextLeaf();
        int parent = code[i];
        if (--deg[parent] == 0)
            addLeaf(parent);
        cout << leaf << " " << parent << "\n";
    }
    return 0;
}
