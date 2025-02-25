#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define qforn(i,n) for(i=0;i<int(n);i++)

#define SIZE(c) int((c).size())

using tint = long long;

namespace NotebookAji
{
    const int MAX_N = 2000;
    struct Eje{ long f,m; long d(){return m-f;}};
    typedef map <int, Eje> MIE; MIE red[MAX_N];
    int N,F,D;
    void iniG(int n, int f, int d){N=n; F=f; D=d;fill(red, red+N, MIE());}
    void aEje(int d, int h, int m){
      red[d][h].m=m;red[d][h].f=red[h][d].m=red[h][d].f=0;
    }
    #define DIF_F(i,j) (red[i][j].d())
    #define DIF_FI(i)  (i->second.d())
    int v[MAX_N];
    long camAu(){
      fill(v, v+N,-1);
      queue<int> c;
      c.push(F);
      while(!(c.empty()) && v[D]==-1){
        int n = c.front(); c.pop();
        for(MIE::iterator i = red[n].begin(); i!=red[n].end(); i++){
          if(v[i->first]==-1 && DIF_FI(i) > 0){
            v[i->first]=n;
            c.push(i->first);
          }
        }
      }
      if(v[D]==-1)return 0;
      int n = D;
      long f = DIF_F(v[n], n);
      while(n!=F){
        f = min(f, DIF_F(v[n], n));
        n=v[n];
      }
      n = D;
      while(n!=F){
        red[n][v[n]].f=-(red[v[n]][n].f+=f);
        n=v[n];
      }
      return f;
    }
    long flujo(){long tot=0, c;do{tot+=(c=camAu());}while(c>0); return tot;}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k;
    cin >> n >> m >> k;
    const int SOURCE = n+m;
    const int SINK = n+m+1;
    NotebookAji::iniG(n+m+2, SOURCE, SINK);
    forn(i,n)
        NotebookAji::aEje(SOURCE, i, 1);
    forn(j,m)
        NotebookAji::aEje(n+j, SINK, 1);
    forn(index,k)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        NotebookAji::aEje(a, n+b, 1);
    }
    cout << NotebookAji::flujo() << "\n";
    forn(i,n)
    forn(j,m)
    if (NotebookAji::red[i][n+j].f > 0)
        cout << i+1 << " " << j+1 << "\n";
    return 0;
}
