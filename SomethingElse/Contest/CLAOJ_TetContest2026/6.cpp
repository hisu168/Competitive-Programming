#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;
int n, q;
int p[N];
vector<int> g[N];

namespace subtask2 {
    void solve(int n) {
        while(q--) {
            int tv; cin >> tv;
            if(tv == 1) {
                int u, v;
                cin >> u >> v;
                swap(p[u], p[v]);
            }
            else if(tv == 2) {
                int u, v;
                cin >> u >> v;
                
                queue<int> q;
                q.push(u);
                vector<int> trace(n + 2, -1);
                vector<bool> vis(n + 2, false);
                vis[u] = true;
                
                while(q.size()) {
                    int cur = q.front(); q.pop();

                    if(cur == v) break;

                    for(int next : g[cur]) if(vis[next] == false) {
                        vis[next] = true;
                        trace[next] = cur;
                        q.push(next);
                    }
                }
                
                vector<bool> kt(n + 2, false);
                int cur = v;
                while(cur != -1) {
                    kt[p[cur]] = true;
                    if(cur == u) break;
                    cur = trace[cur];
                }
                
                int ans = 0;
                while(kt[ans] == true) ans++;
                cout << ans << ed;
            }
            else {
                int m; cin >> m;
                int ans = 0;
                
                for(int i = 1; i <= n; i++) {
                    auto dfs = [&](auto self, int u, int par, bitset<305> mask) -> void {
                        mask[p[u]] = 1;
                        
                        if(u >= i) {
                            int cur = 0;
                            while(mask[cur] == 1) cur++;
                            if(cur == m) ans++;
                        }
                        
                        for(int v : g[u]) if(v != par) {
                            self(self, v, u, mask);
                        }
                    };
                    
                    bitset<305> mask;
                    dfs(dfs, i, 0, mask);
                }

                cout << ans << ed;
            }
        }
    }
}

namespace subtask3 {
    const int INF = 1e18;
    int pos[N];
    
    struct Node {
        int mn, mx;
    } st[4 * N];

    Node merge(const Node &a, const Node &b) {
        return {min(a.mn, b.mn), max(a.mx, b.mx)};
    }

    void build(int id, int l, int r) {
        if(l == r) {
            st[id] = {pos[l], pos[l]};
            return;
        }
        int mid = l + r >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        st[id] = merge(st[id << 1], st[id << 1 | 1]);
    }

    void update(int id, int l, int r, int k, int val) {
        if(l == r) {
            st[id] = {val, val};
            return;
        }
        int mid = l + r >> 1;
        if(k <= mid) update(id << 1, l, mid, k, val);
        else update(id << 1 | 1, mid + 1, r, k, val);
        st[id] = merge(st[id << 1], st[id << 1 | 1]);
    }

    Node get(int id, int l, int r, int u, int v) {
        if(u > r || v < l) return {INF, -INF};
        if(u <= l && r <= v) return st[id];
        int mid = l + r >> 1;
        return merge(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
    }

    int findMex(int id, int l, int r, int u, int v) {
        if(l == r) return l;
        int mid = l + r >> 1;
        
        if(st[id << 1].mn >= u && st[id << 1].mx <= v) return findMex(id << 1 | 1, mid + 1, r, u, v);
        else return findMex(id << 1, l, mid, u, v);
    }

    void solve(int n) {
        fill(pos, pos + n + 2, -1);
        for(int i = 1; i <= n; i++) pos[p[i]] = i;

        build(1, 0, n);

        while(q--) {
            int type; cin >> type;
            if(type == 1) {
                int u, v; cin >> u >> v;
                int x = p[u],
                    y = p[v];
                
                swap(p[u], p[v]);
                
                pos[x] = v;
                pos[y] = u;
                
                update(1, 0, n, x, v);
                update(1, 0, n, y, u);
            } 
            else if(type == 2) {
                int u, v; cin >> u >> v;
                if(u > v) swap(u, v);
                cout << findMex(1, 0, n, u, v) << ed;
            } 
            else {
                int m; cin >> m;
                if(m == 0) {
                    int l = pos[0] - 1,
                        r = n - pos[0];
                    cout << l * (l + 1) / 2 + r * (r + 1) / 2 << ed;
                }
                else {
                    Node ret = get(1, 0, n, 0, m - 1);

                    if(ret.mn == INF) {
                        cout << 0 << ed;
                        continue;
                    }
                    
                    int ans = 0;
                    if(pos[m] < ret.mn) ans = (ret.mn - pos[m]) * (n - ret.mx + 1);
                    else if(pos[m] > ret.mx) ans = ret.mn * (pos[m] - ret.mx);

                    cout << ans << ed;
                }
            }
        }
    }
}



void solve(int iTest) {
    int theta; cin >> theta;

    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> p[i];

    for(int i = 2; i <= n; i++) {
        int u; cin >> u;
        g[u].push_back(i);
        g[i].push_back(u);
    }

    if(theta <= 2) subtask2::solve(n);
    else if(theta == 3) subtask3::solve(n);
    else if(theta == 4) subtask4::solve();
    else {
        
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