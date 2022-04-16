#include <bits/stdc++.h>

using int64 = long long;
using namespace std;

const int maxn = 1<<14;
const int memsize = maxn * sizeof(int);
const int LG = 17;
const int mod = 1e9 + 7;

struct Edge {
    int v;
    int type;
    int x; 
};

int Q, root, cntNode, cntQuery;
int par[maxn];
int subtree[maxn];
int answers[maxn];
vector<Edge> g[maxn];
vector<pair<int,int>> queries[maxn];

int add(int node, int type, int x) {
    int newNode = ++cntNode;
    g[node].push_back({newNode, type, x});
    par[newNode] = node;
    return newNode;
}

void dfs_prep(int v) {
    subtree[v] = 1;
    for(auto [s, t, x]: g[v]) {
        dfs_prep(s);
        subtree[v] += subtree[s];
    }
    sort(g[v].begin(), g[v].end(), [&](Edge x, Edge y){
        return subtree[x.v] > subtree[y.v];
    });
}

int cur;
int f[LG][maxn];

void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

void apply(int *f, int *g, int type, int x) {
    memset(g, 0, memsize);
    for(int i = 0; i < maxn; ++i) {
        add(g[i], f[i]);
        if (type == 0) add(g[i^x], f[i]);
        else if (type == 1) add(g[i&x], f[i]);
        else add(g[i|x], f[i]);
    }
}

void dfs_solve(int v) {
    for(auto [id, x]: queries[v]) {
        answers[id] = f[cur][x];
    }
    if (g[v].size() == 0) return;
    int pos = ++cur;

    for(int i = 1; i < g[v].size(); ++i) {
        auto [s, type, x] = g[v][i];
        apply(f[pos-1], f[pos], type, x);
        dfs_solve(s);
        assert(pos == cur);
    }

    --cur;
    {
        auto [s, type, x] = g[v].front();
        apply(f[pos-1], f[pos], type, x);
        memcpy(f[pos-1], f[pos], memsize);
        dfs_solve(s);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> Q;
    for(int i = 0; i < Q; ++i) {
        int x;
        string type; cin >> type;
        if (type == "XOR") {
            cin >> x;
            root = add(root, 0, x);
        } else if (type == "AND") {
            cin >> x;
            root = add(root, 1, x);
        } else if (type == "OR") {
            cin >> x;
            root = add(root, 2, x);
        } else if (type == "REMOVE") {
            root = par[root];
        } else {
            cin >> x;
            queries[root].emplace_back(cntQuery++, x);
        }
    }

    f[0][0] = 1;
    dfs_prep(0);
    dfs_solve(0);

    for(int i = 0; i < cntQuery; ++i) cout << answers[i] << "\n";

    return 0;
}