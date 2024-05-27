#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)

#define DBG(x) cerr << #x << " = " << (x) << endl
#define SIZE(c) int((c).size())

const int MAX_NODES = 610000;

const int INF = 1000000000;

struct Node *root();
struct Node *nullNode();

struct Node
{
    int pos;
    Node* link;
    map<char, Node*> children;
    Node() {pos = INF;}
    
    Node *jump(char c)
    {
        Node *candidate = this;
        map<char, Node*>::const_iterator it;
        while (candidate != nullNode() && (it = candidate->children.find(c)) == candidate->children.end())
            candidate = candidate->link;
        if (candidate != nullNode())
            return it->second;
        else
            return root();
    }
    
} nodes[MAX_NODES];

Node *nextNode;

Node *nullNode()
{
    return nodes;
}

Node *root()
{
    return nodes+1;
}

void initAho()
{
    nextNode = nodes+2;
}

Node *insert(const string &w)
{
    Node *node = root();
    for (char c : w)
    {
        auto it = node->children.find(c);
        if (it == node->children.end())
            node = node->children[c] = nextNode++; // INIT NODE IF NEEDED
        else
            node = it->second;
    }
    return node;
}

struct Event
{
    Node *node, *parent;
    char c;
};

Event eventQueue[MAX_NODES];
int eventQueueFront, eventQueueBack;

void ahoComputeLinks()
{
    root()->link = nullNode();
    eventQueueFront = eventQueueBack = 0;
    #define PUSH_CHILDREN(node) for (auto it : node->children) eventQueue[eventQueueBack++] = {it.second, node, it.first};
    PUSH_CHILDREN(root());
    while (eventQueueBack != eventQueueFront)
    {
        Event e = eventQueue[eventQueueFront++];
        e.node->link = e.parent->link->jump(e.c);
        PUSH_CHILDREN(e.node);
    }
}

void ahoRun(const string &s)
{
    Node *node = root();
    // node->pos = 0; // Report EMPTY STRING MATCHING ON INDEX 0, IF RELEVANT
    forsn(pos, 1, SIZE(s)+1)
    {
        node = node->jump(s[pos-1]);
        node->pos = min(node->pos, pos); // REPORT LONGEST MATCH ENDING AT pos
    }
}

void propagateMatchInformation()
{
    dforn(i, eventQueueBack)
    {
        Node *node = eventQueue[i].node;
        node->link->pos = min(node->link->pos, node->pos);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initAho();
    string s;
    cin >> s;
    int k;
    cin >> k;
    string w;
    vector<Node *> patternNodes(k);
    vector<int> patternLengths(k);
    forn(i,k)
    {
        cin >> w;
        patternLengths[i] = SIZE(w);
        patternNodes[i] = insert(w);
    }
    
    ahoComputeLinks();
    ahoRun(s);
    propagateMatchInformation();
    forn(i,k)
    {
        int pos = patternNodes[i]->pos;
        if (pos == INF)
            cout << "-1\n";
        else
            cout << 1 + pos - patternLengths[i] << "\n";
    }
    return 0;
}
