#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, ax, ay, bx, by;
    cin >> n >> ax >> ay >> bx >> by;

    vector<int> x(n), y(n);
    for(int &z : x) cin >> z;
    for(int &z : y) cin >> z;

    map<int, vector<int>> mp;
    for(int i = 0; i < n; i++) mp[x[i]].push_back(y[i]);
    mp[ax].push_back(ay);
    mp[bx].push_back(by);

    int ans = bx - ax;
    vector<int> v1, v2;
    for(auto &[x, z] : mp){
        int mx = *max_element(z.begin(), z.end()),
            mn = *min_element(z.begin(), z.end());

        ans += (mx - mn);
        v1.push_back(mn);
        v2.push_back(mx);
    }

    int m = v1.size();
    vector<vector<int>> dp(2, vector<int>(m + 2, 1e16));
    dp[0][0] = dp[1][0] = 0;

    for(int i = 1; i < m; i++){
        dp[0][i] = min(dp[0][i - 1] + abs(v2[i - 1] - v1[i]), dp[1][i - 1] + abs(v1[i - 1] - v1[i]));
        dp[1][i] = min(dp[0][i - 1] + abs(v2[i - 1] - v2[i]), dp[1][i - 1] + abs(v1[i - 1] - v2[i]));
    }

    cout << ans + min(dp[0][m - 1], dp[1][m - 1]) << ed;
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