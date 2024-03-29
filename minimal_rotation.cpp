#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

const int MAXN = 2*1100000;

int z[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    const int N = int(s.size());
    s += s;
    // Se prueba la rotacion que empieza en i
    int A = 0,B = 0; // Invariante: [A,B) es prefijo de la bestRot, o sea coincide con [bestRot, bestRot + B-A )
    int bestRot = 0;
    forsn(i, 1, N)
    {
        int &myZ = z[i-bestRot];
        if (B > i)
        {
            assert(A > 0);
            assert(A < i);
            myZ = min(z[i-A], B-i);
            assert(myZ >= 0);
        }
        else
            myZ = 0;
        while (i + myZ < 2*N && s[bestRot + myZ] == s[i + myZ])
        {
            myZ++;
            assert(i+myZ > B);
        }
        if (i + myZ > B)
        {
            A = i;
            B = i + myZ;
        }
        // Esta parte es en definitiva el unico extra al algoritmo Z, lo anterior es el algoritmo Z en si mismo. 
        if (i + myZ < 2*N && s[i + myZ] < s[bestRot + myZ])
        {
            bestRot = i;
            assert(myZ == B-i);
            if (myZ != 0)
            {
                forsn(j, 1, myZ)
                if (z[j] >= myZ - j)
                {
                    A = i+j;
                    while (A + z[j] < 2*N && s[A+z[j]] == s[bestRot + z[j]]) z[j]++; // fix invariante para la iteracion siguiente (si B > i tiene que ser A < i
                    //B = i+myZ; // Ya era igual
                    i = A;
                    goto chau;
                }
                // Ninguno cumple! Podemos saltear la exploracion
                i = B-1;
chau:;
            }
        }
    }
    cout << s.substr(bestRot,N) << "\n";
    return 0;
}
