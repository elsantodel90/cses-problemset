#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)

#define DBG(x) {cerr << #x << " = " << (x) << endl;}
#define RAYA {cerr << "=======================================" << endl;}

const int MAXN = 200000;

vector<int> g[MAXN];

bool inStack[MAXN];
int discoveryTime[MAXN];
int low[MAXN];
int component[MAXN];
stack<int> componentStack;
int componentRoot[MAXN];

int totalComponents = 0;
int currentTime = 1;

#define WHITE(x) (discoveryTime[x] == 0)

vector<int> gc[MAXN];
vector<int> gct[MAXN]; // Traspose Graph: Used just for reconstruction of the problem's solution

void tarjan(int x)
{
    componentStack.push(x);
    inStack[x] = true;
    low[x] = discoveryTime[x] = currentTime++;
      
    for (int y : g[x])
    if (WHITE(y))
    {
        tarjan(y);
        low[x] = min(low[x], low[y]);
    }
    else if (inStack[y]) // This is the appropriate check, both for GRAY and BLACK nodes
        low[x] = min(low[x], discoveryTime[y]);
    
    if (low[x] == discoveryTime[x])
    {
        // Component found!
        const int currentComponent = totalComponents++;
        componentRoot[currentComponent] = x;
        vector<int> nodes;
        do
        {
            nodes.push_back(componentStack.top());
            inStack[componentStack.top()] = false;
            componentStack.pop();
            component[nodes.back()] = currentComponent;
        } while (nodes.back() != x);
        
        for (int node : nodes)
        for (int neighbor : g[node])
        {
            assert(component[neighbor] >= 0);
            if (component[neighbor] != currentComponent)
            {
                gc[currentComponent].push_back(component[neighbor]);
                gct[component[neighbor]].push_back(currentComponent);
            }
        }
    }
}

void fillSinks(vector<int> &sinks, vector<int> &reachableSink, vector<int> graph[], int start, int delta, int stop)
{
    for (int i=start; i != stop; i+= delta)
    {
        if (graph[i].empty())
        {
            reachableSink[i] = i;
            sinks.push_back(i);
        }
        else
            reachableSink[i] = reachableSink[graph[i][0]];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    forn(i,n)
        component[i] = -1; // Just for safety
    forn(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }
    forn(i,n)
    if (WHITE(i))
        tarjan(i);
    // gc is now the condensation graph, having totalComponents nodes
    assert(totalComponents > 0);
    if (totalComponents == 1)
        cout << "0\n";
    else
    {
        vector<int> sources, sinks;
        vector<int> reachableSource(totalComponents, -1);
        vector<int> reachableSink(totalComponents, -1);
        fillSinks(sinks  , reachableSink  , gc , 0                ,  1, totalComponents);
        fillSinks(sources, reachableSource, gct, totalComponents-1, -1, -1);
        cout << max(sources.size(), sinks.size()) << "\n";
        // Hacer la operatoria de asegurar un camino
        vector<char> usedSources(totalComponents, 0);
        vector<char> usedSinks(totalComponents, 0);
        vector<pair<int,int>> paths;
        forn(step, 2)
        {
            for(int s : (step ? sources : sinks))
            {
                int t = (step ? reachableSink : reachableSource)[s];
                if (step == 0)
                    swap(s,t);
                if (!usedSources[s] && !usedSinks[t])
                {
                    usedSinks[t] = 1;
                    usedSources[s] = 1;
                    paths.emplace_back(s,t);
                }
            }
        }
        vector<int> remainingSources, remainingSinks;
        #define clean(nodes, used, remaining) {for (int x : nodes) if (!used[x]) remaining.push_back(x);}
        clean(sources, usedSources, remainingSources);
        clean(sinks  , usedSinks  , remainingSinks  );
        assert(!paths.empty());
        #define print(a,b) {cout << componentRoot[a]+1 << " " << componentRoot[b]+1 << "\n";}
        forn(i, paths.size()-1)
            print(paths[i].second, paths[i+1].first);
        print(paths.back().second, paths.front().first);
        int sourceIndex = 0, sinkIndex = 0;
        int totalSteps = int(max(remainingSources.size(), remainingSinks.size()));
        // After fixing totalSteps, we add sentinel values to prevent empty collection problems
        remainingSources.push_back(sources.front());
        remainingSinks.push_back(sinks.front());
        forn(steps, totalSteps)
        {
            print(remainingSinks[sinkIndex], remainingSources[sourceIndex]);
            sourceIndex = (sourceIndex + 1) % int(remainingSources.size());
            sinkIndex   = (sinkIndex   + 1) % int(remainingSinks.size());
        }
    }
    return 0;
}
