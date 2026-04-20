#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n + 2, 0), compress;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        compress.push_back(a[i]);
    }
    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());

    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(compress.begin(), compress.end(), a[i]) - compress.begin() + 1;
    }

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            dp[i][j] = 2;
        }
    }

    vector<int> pre(n + 2, 0);
    for(int i = 1; i <= n; i++) {
        // cout << i << ed;
        for(int j = 0; j <= n; j++) pre[j] = 0;
        for(int j = 1; j < i; j++) pre[a[j]] = max(pre[a[j]], dp[j][i]);
        for(int j = 1; j <= n; j++) pre[j] = max(pre[j], pre[j - 1]);
        // for(int j = 1; j <= n; j++) cout << j << ' ' << pre[j] << ed;
        
        for(int j = i + 1; j <= n; j++) {
            dp[i][j] = max(dp[i][j], pre[a[j] - 1] + 1);
            // cout << j << ' ' << dp[i][j] << ed;
        }
    }

    int ans = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) ans = max(ans, dp[i][j]);
    }

    cout << ans;
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