// Chaiyo...
#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 360 + 5;
int pos[100005][N];
vector<pair<int, int>> dp[N][N];
vector<pair<int, int>> dq[N];

struct DSU {
    int n;
    vector<int> lab;

    DSU(int _n) : n(_n) {
        lab.assign(n + 2, -1);
    }

    int root(int n) {
        if(lab[n] < 0) return n;
        return lab[n] = root(lab[n]);
    }

    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if(x != y) {
            if(x > y) swap(x, y);
            lab[x] = y;
            return true;
        }
        return false;
    }
};

void solve(int iTest) {
    int n, k; cin >> n >> k;
    vector<int> a(n + 2, 0);

    for(int i = 0; i <= k; i++) pos[i].clear();
    for(int c = 0; c <= k; c++)
        for(int v = 0; v <= k; v++) dp[c][v].clear();

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
//        pos[a[i]].push_back(i);
//        for(int j = 1; j <= min(a[i], k); j++)
//            pos[j].push_back(i);
    }

    for(int j = 0; j <= k; j++) pos[n + 1][j] = n + 1;
    for(int i = n; i >= 1; i--){
        for(int j = 0; j <= k; j++) {
            if(a[i] >= j) pos[i][j] = i;
            else pos[i][j] = pos[i + 1][j];
        }
    }

    dp[0][0].push_back({0, 0});
    int ans = 0;

    vector<vector<pair<int, int>>> dq(k + 1);
    DSU dsu(n);

    for(int c = 0; c <= k; c++) {
//        for(int id : pos[v - 1])
//            dsu.unite(id, id + 1);
//        if(dsu.root(0) > n) continue;

//        for(int c = 0; c <= k; c++) dq[c].clear();
//        cout << v << ": " << ed;

        for(int v = 0; v <= c; v++) if(dp[c][v].size() > 0) {
            for(int prev_v = 0; prev_v < v; prev_v++) {
                for(auto &[x, y] : dp[c][prev_v]) {
                    int id = dsu.root(x + 1);
                    if(1 <= id && id <= n) {
                        int val = (id - x) * prev_v;
                        dq[c + v].push_back({id, y + val});
                    }
                }
            }
        }

        for(int c = 1; c <= k; c++) {
//            cout << dp[v][c].size() << ed;
            if(dq[c].empty()) continue;

            sort(dq[c].begin(), dq[c].end());

            int mx = -1;
            for(auto &[x, y] : dq[c]) {
                if(y > mx) {
                    mx = y;
                    dp[c][v].push_back({x, y});

                    int val = mx + (n - x + 1) * v;
//                    cout << c << ' ' << x << ' ' << y << ' ' << val << ed;
                    ans = max(ans, val);
                }
            }
        }
    }

    cout << ans << ed;
}

#define TASK "main"

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

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
