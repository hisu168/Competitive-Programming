#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, mod = 1e9 + 7;

int n, m;
int w[N];
vector<int> g[N];

int bpow(int n, int m) {
    int res = 1;
    for(; m; m >>= 1) {
        if(m & 1) res = res * n % mod;
        n = n * n % mod;
    }
    return res;
}

namespace subtask2 {
    bool check() {
        for(int i = 1; i < n; i++) {
            for(int v : g[i]) if(v != i + 1) return false;
        }
        return true;
    }

    void solve() {
        vector<int> ans(n + 2, 0);
        int sum = 0, sqsum = 0;
        
        for(int i = n; i >= 2; i--) {
            sum = (sum + w[i] + mod) % mod;
            sqsum = (sqsum + w[i] * w[i] % mod) % mod;
            
            int val = (sum * sum % mod - sqsum + mod) % mod;
            ans[i - 1] = (val * bpow(2, mod - 2)) % mod;
        }

        for(int i = 1; i <= n; i++) cout << ans[i] << ed;
    }
}

namespace subtask3 {
    int ans[N];

    bool check() {
        vector<int> inDeg(n + 2, 0);
        for(int i = 1; i <= n; i++) {
            for(int v : g[i]) {
                inDeg[v]++;
                if(inDeg[v] > 1) return false;
            }
        }
        return true;
    }

    pair<int, int> dfs(int u) {
        int s = (w[u] + mod) % mod,
            sq = w[u] * w[u] % mod;
            
        for(int v : g[u]) {
            pair<int, int> res = dfs(v);
            s = (s + res.first) % mod;
            sq = (sq + res.second) % mod;
        }

        int sum = (s - w[u] + mod * 2) % mod,
            sqsum = (sq - w[u] * w[u] % mod + mod) % mod;
        
        int val = (sum * sum % mod - sqsum + mod) % mod;
        ans[u] = val * bpow(2, mod - 2) % mod;

        return {s, sq};
    }

    void solve() {
        vector<int> inDeg(n + 2, 0);
        for(int i = 1; i <= n; i++) {
            for(int v : g[i]) inDeg[v]++;
        }

        for(int i = 1; i <= n; i++) {
            if(inDeg[i] == 0) dfs(i);
        }

        for(int i = 1; i <= n; i++) cout << ans[i] << ed;
    }
}

namespace subtask4 {
    int ans[N];
    int timer = 0;

    bool check() {
        return n <= 2000 && m <= 4000;
    }

    void solve() {
        vector<int> inDeg(n + 2, 0);
        for(int u = 1; u <= n; ++u) {
            for(int v : g[u]) inDeg[v]++;
        }
        
        vector<int> roots;
        for(int i = 1; i <= n; i++) {
            if(inDeg[i] == 0) roots.push_back(i);
        }

        timer++;
        queue<int> q;
        vector<int> nodes, vis(n + 2, 0);

        for(int u : roots) {
            vis[u] = timer;
            q.push(u);
            nodes.push_back(u);
        }

        while(q.size()) {
            int u = q.front(); q.pop();
            for(int v : g[u]){
                if(vis[v] != timer) {
                    vis[v] = timer;
                    q.push(v);
                    nodes.push_back(v);
                }
            }
        }

        vector<bool> reachable(n + 2, false);
        for(int u : nodes) reachable[u] = true;

        for(int i = 1; i <= n; i++) {
            if(reachable[i] == false || g[i].size() == 0) continue;

            timer++; 
            while(!q.empty()) q.pop();

            for(int u : roots) if(u != i) {
                vis[u] = timer;
                q.push(u);
            }

            while(q.size()) {
                int u = q.front(); q.pop();
                for(int v : g[u]) if(v != i && vis[v] != timer) {
                    vis[v] = timer;
                    q.push(v);
                }
            }

            int s = 0, sq = 0;
            for(int j : nodes) {
                if(j == i) continue;

                if(vis[j] != timer) {
                    s = (s + w[j] + mod) % mod;
                    sq = (sq + w[j] * w[j] % mod) % mod;
                }
            }
            
            int val = (s * s % mod - sq + mod) % mod;
            ans[i] = val * bpow(2, mod - 2) % mod;
        }

        for(int i = 1; i <= n; i++) cout << ans[i] << ed;
    }
}

void solve(int iTest) {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }

    if(subtask2::check()) subtask2::solve();
    else if(subtask3::check()) subtask3::solve();
    else subtask4::solve();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    #define TASK "main"
    if(fopen(TASK ".inp", "r")) {
        freopen(TASK ".inp", "r", stdin);
        freopen(TASK ".ans", "w", stdout);
    }
    else if(fopen("main.inp", "r")) {
        freopen("main.inp", "r", stdin);
        freopen("main.ans", "w", stdout);
    }
    
    int T = 1;
    // cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}