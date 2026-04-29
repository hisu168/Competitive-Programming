#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<vector<int>> g(n + 2);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<bool>> dp(n + 2, vector<bool> (3, false));

    auto dfs = [&](int u, int p, auto self) -> void {
        bool isLeaf = true;
        bool cur[3] = {true, false, false};

        for(int v : g[u]) if(v != p) {
            isLeaf = false;
            self(v, u, self);

            bool nxt[3] = {false, false, false};
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    nxt[(i + j) % 3] = (nxt[(i + j) % 3] || (cur[i] && dp[v][j]));
                }
            }

            for(int i = 0; i < 3; i++) cur[i] = nxt[i];
        }

        if(isLeaf == true) {
            dp[u][0] = dp[u][2] = false;
            dp[u][1] = true;
        }
        else {
            for(int i = 0; i < 3; i++) dp[u][i] = cur[i];
            dp[u][1] = true;
        }
    };

    dfs(1, 0, dfs);

    if(dp[1][0] == true) cout << "YES" << ed;
    else cout << "NO" << ed;
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