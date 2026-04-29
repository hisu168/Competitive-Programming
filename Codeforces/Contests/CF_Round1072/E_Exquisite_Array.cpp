#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

struct DSU {
    int n;
    vector<int> lab;

    DSU(int _n) : n(_n) {
        lab.assign(n, -1);
    }

    int root(int u) {
        if(lab[u] < 0) return u;
        return lab[u] = root(lab[u]);
    }

    void unite(int u, int v, int &ans) {
        u = root(u); v = root(v);
        if(u != v) {
            ans -= -lab[u] * (-lab[u] + 1) / 2;
            ans -= -lab[v] * (-lab[v] + 1) / 2;
            lab[u] += lab[v];
            lab[v] = u;
            ans += -lab[u] * (-lab[u] + 1) / 2;
        }
    }
};

void solve(int iTest) {
    int n; cin >> n;
    vector<int> p(n + 2, 0);
    for(int i = 1; i <= n; i++) cin >> p[i];

    vector<vector<int>> pos(n + 2);
    for(int i = 1; i < n; i++) {
        pos[abs(p[i] - p[i + 1])].push_back(i);
    }

    DSU dsu(n);
    vector<bool> vis(n + 2, false);
    vector<int> ans(n + 2, 0);
    int res = 0;

    for(int k = n - 1; k >= 1; k--) {
        for(int id : pos[k]) {
            vis[id] = true;
            res++;

            if(id > 1 && vis[id - 1] == true) dsu.unite(id - 1, id, res);
            if(id < n - 1 && vis[id + 1] == true) dsu.unite(id, id + 1, res);
        }
        ans[k] = res;
    }

    for(int k = 1; k < n; k++) cout << ans[k] << ' ';
    cout << ed;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    #define TASK "main"
    if(fopen(TASK ".inp", "r")) {
        freopen(TASK ".inp", "r", stdin);
        freopen(TASK ".out", "w", stdout);
    }
    else if(fopen("main.inp", "r")) {
        freopen("main.inp", "r", stdin);
        freopen("main.out", "w", stdout);
    }

    int T = 1;
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}