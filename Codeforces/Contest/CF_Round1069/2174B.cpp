#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, k; cin >> n >> k;
    vector<int> a(n + 2, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> pos(k + 2, n + 1);
    for(int i = 1; i <= n; i++) pos[a[i]] = min(pos[a[i]], i);
    for(int i = k - 1; i >= 0; i--) pos[i] = min(pos[i], pos[i + 1]);

    vector<vector<int>> dp(k + 2, vector<int> (k + 2, 0));
    int ans = 0;
    for(int i = 1; i <= k; i++) {
        for(int j = i; j <= k; j++) {
            for(int u = 0; u <= i; u++) {
                dp[i][j] = max(dp[i][j], dp[u][j - i] + (n - pos[i] + 1) * (i - u));
            }
            ans = max(ans, dp[i][j]);
        }
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