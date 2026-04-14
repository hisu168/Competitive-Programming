#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    s = ' ' + s;

    vector<int> dp(n + 2, 0), pre(n + 2, 0), best(n + 2, 0);

    while(q--) {
        int l, r; cin >> l >> r;

        int ans = 1;
        best[l - 1] = 1e7;
        best[l] = dp[l] = 1;
        pre[l] = 0;

        for(int i = l + 1; i <= r; i++) {
            int j = pre[i - 1];

            while(j > 0 && s[l + j] != s[i]) j = pre[l + j - 1];
            if(s[l + j] == s[i]) j++;
            pre[i] = j;

            best[i] = min(i - l + 1, best[l + pre[i] - 1]);

            dp[i] = max(dp[i], dp[i - best[i]] + 1);
            ans += dp[i];

            // cout << "i: " << i << ", pre: " << pre[i] << ", best: " << best[i] << ", dp: " << dp[i] << ed;
            // cout << "j: " << j << ed;
        }

        cout << ans << ed;

        for(int i = l - 1; i <= r; i++) {
            dp[i] = pre[i] = best[i] = 0;
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
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}