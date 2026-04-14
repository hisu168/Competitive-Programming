#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 3e5 + 5;
const int mod = 1e9 + 7;
const int INV2 = 500000004;
int n, q;
int a[N];
vector<int> g[N];
int par[N], h[N], heavy[N], head[N], pos[N], sz[N];
int timer = 0;

struct Node {
    int sum, sq, mn, mx;
    Node() : sum(0), sq(0), mn(2e18), mx(-2e18) {}
    Node(int _sum, int _sq, int _mn, int _mx) : sum(_sum), sq(_sq), mn(_mn), mx(_mx) {}
} st[N * 4];

Node merge(const Node &l, const Node &r) {
    Node res;
    res.sum = (l.sum + r.sum) % mod;
    res.sq = (l.sq + r.sq) % mod;
    res.mn = min(l.mn, r.mn);
    res.mx = max(l.mx, r.mx);
    return res;
}

void update(int id, int l, int r, int k, int val) {
    if(l == r) {
        st[id] = Node(val % mod, val * val % mod, val, val);
        return;
    }
    int mid = l + r >> 1;
    if(k <= mid) update(id << 1, l, mid, k, val);
    else update(id << 1 | 1, mid + 1, r, k, val);
    st[id] = merge(st[id << 1], st[id << 1 | 1]);
}

Node get(int id, int l, int r, int u, int v) {
    if(u > r || v < l) return Node();
    if(u <= l && r <= v) return st[id];
    int mid = l + r >> 1;
    return merge(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}

void dfs_sz(int u, int p) {
    sz[u] = 1;
    heavy[u] = -1;
    for(int v : g[u]) if(v != p) {
        h[v] = h[u] + 1;
        par[v] = u;

        dfs_sz(v, u);

        sz[u] += sz[v];
        if(heavy[u] == -1 || sz[v] > sz[heavy[u]]) {
            heavy[u] = v;
        }
    }
}

void dfs_hld(int u, int h) {
    head[u] = h;
    pos[u] = ++timer;

    if(heavy[u] != -1) dfs_hld(heavy[u], h);

    for(int v : g[u]) if(v != par[u] && v != heavy[u]) {
        dfs_hld(v, v);
    }
}

Node queryPath(int u, int v) {
    Node res;
    while(head[u] != head[v]) {
        if(h[head[u]] > h[head[v]]) swap(u, v);
        res = merge(res, get(1, 1, n, pos[head[v]], pos[v]));
        v = par[head[v]];
    }
    if(h[u] > h[v]) swap(u, v);
    res = merge(res, get(1, 1, n, pos[u], pos[v]));
    return res;
}

void solve(int iTest) {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_sz(1, 0);
    dfs_hld(1, 1);

    for(int i = 1; i <= n; i++) {
        update(1, 1, n, pos[i], a[i]);
    }

    while(q--) {
        int tv;
        cin >> tv;
        if(tv == 1) {
            int u, v;
            cin >> u >> v;
            update(1, 1, n, pos[u], v);
        }
        else if(tv == 2) {
            int u, v;
            cin >> u >> v;
            Node res = queryPath(u, v);
            if(res.mn == res.mx) cout << "Noooo" << ed;
            else cout << "Happy New Year 2026!" << ed;
        }
        else {
            int u, v;
            cin >> u >> v;
            Node res = queryPath(u, v);
            
            int ans = (res.sum * res.sum % mod - res.sq + mod) % mod * INV2 % mod;
            cout << ans << ed;
        }
    }
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
    // cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}