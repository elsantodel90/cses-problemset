typedef long long tint;
const int MAXN = 100000;
int v[MAXN];

struct Item {
    int index, den;
    int num() const { return v[index]; }
    tint diff(const Item &o) const {
        return tint(num()) * o.den - tint(o.num()) * den;
    }
    bool operator <(const Item &o) const {
        tint dif = diff(o);
        if (dif != 0)
            return dif < 0;
        return index < o.index;
    }
    int ceiling() const { return (num()+den-1) / den; }
    int floor() const { return num() / den; }
    Item next() const { return {index, den+1}; }
};

struct Option {
    int meetpoint, value;
    bool operator>(const Option &o) const { return value > o.value; }
};


int main() {
    int n,m;
    cin >> n >> m;
    forn(i,n)
        cin >> v[i];
    // Generate "enough items"
    vector<Item> items;
    priority_queue<Item> candidates;
    forn(i,n)
        candidates.push({i, 1});
    assert(m > 0);
    int remainingCuts = m;
    set<int> positions;
    while (remainingCuts > 0) {
        auto best = candidates.top(); candidates.pop();
        items.push_back(best);
        candidates.push(best.next());
        if (best.den == 1)
            positions.insert(SIZE(items)-1);
        else
            remainingCuts--;
    }
    while (!candidates.empty()) {
        items.push_back(candidates.top());
        if (candidates.top().den == 1)
            positions.insert(SIZE(items)-1);
        candidates.pop();
    }
    // Compute next and prev to allow movements
    vector<int> nextItem(SIZE(items));
    vector<int> prevItem(SIZE(items));
    vector<int> lastPos(n,-1);
    forn(i,SIZE(items)) {
        int index = items[i].index;
        prevItem[i] = lastPos[index];
        if (lastPos[index] >= 0)
            nextItem[lastPos[index]] = i;
        lastPos[index] = i;
    }
    forn(i,n)
        nextItem[lastPos[i]] = SIZE(items);
    // Compute base greedy "maximize minimum stick"
    vector<int> ret(m+1);
    set<int> auxPos = positions;
    int cutsDone = 0;
    int nextI = 0;
    while(cutsDone < m) {
        if (!auxPos.count(nextI)) {
            assert(auxPos.erase(prevItem[nextI]));
            auxPos.insert(nextI);
            cutsDone++;
            ret[cutsDone] = items[*begin(auxPos)].ceiling() - items[*rbegin(auxPos)].floor();
        }
        nextI++;
    }
    // Compute "deviation options" (alternatives to base greedy)
    priority_queue<Option, vector<Option>, greater<Option>> options;
    forsn(k,1,m+1) {
        int previousLeftmost = *begin(positions);
        positions.erase(begin(positions));
        positions.insert(nextItem[previousLeftmost]);
        int leftmost = *begin(positions);
        int rightmost = *rbegin(positions);
        int meetpoint = rightmost - (n-1);
        int value = items[leftmost].ceiling() - items[rightmost].floor();
        // We have an option for total cuts in range [k, meetpoint)
        options.push({meetpoint, value});
        while (!options.empty() && options.top().meetpoint <= k)
            options.pop();
        if (!options.empty())
            ret[k] = min(ret[k], options.top().value);
    }
    forsn(k,1,m+1) {
        if (k > 1)
            cout << " ";
        cout << ret[k];
    }
    cout << "\n";
    return 0;
}
