#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, mod = 998244353;

void solve(int iTest) {
    int n, m; cin >> n >> m;
    vector<int> a(n + 2, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];

    struct Edge {
        int u, v, id;
    };
    vector<Edge> edges;
    vector<vector<pair<int, int>>> rev(n + 2);
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        edges.push_back({u, v, i});
        rev[v].push_back({a[u], i});
    }

    for(int i = 1; i <= n; i++) 
        sort(rev[i].begin(), rev[i].end());

    vector<int> dp(m + 2, -1);
    vector<map<int, int>> memo(n + 2);
    auto calc = [&](int id, auto self) -> int {
        if(dp[id] != -1) return dp[id];

        auto [u, v, i] = edges[id - 1];
        int val = a[v] - a[u],
            &res = dp[id];
        res = 0;
        
        if(val <= 0) return res;

        if(memo[u].count(val)) return res = memo[u][val];

        int cnt = 0;
        auto it = lower_bound(rev[u].begin(), rev[u].end(), make_pair(val, -1ll));

        // cout << id << ed;
        // cout << it->first << ' ' << it->second << ed;
        // for(auto [x, pos] : rev[u]) cout << x << ' ' << pos << ed;

        while(it != rev[u].end() && it->first == val) {
            cnt = (cnt + 1 + self(it->second, self)) % mod;
            it++;
        }

        return res = memo[u][val] = cnt;
    };

    int ans = m;
    for(int i = 1; i <= m; i++) {
        ans = (ans + calc(i, calc)) % mod;
    }
    cout << ans << ed;
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