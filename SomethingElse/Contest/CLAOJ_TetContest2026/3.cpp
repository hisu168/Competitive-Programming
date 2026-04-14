#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;
const int INF = 1e15;
const int mod = 20268386;

void solve(int iTest) {
    int n, s, k; 
    cin >> n >> s >> k;
    
    vector<int> dp(s + 2, INF);
    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        int w, v, a;
        cin >> w >> v >> a;

        int cnt = 1;
        while(a > 0) {
            int take = min(a, cnt),
                weight = take * w;

            for(int j = s; j >= weight; j--) {
                dp[j] = min(dp[j], dp[j - weight] + take * v);
            }

            a -= take;
            cnt <<= 1;
        }
    }

    int ans = 0;
    for(int i = k; i <= s; i += k) {
        if(dp[i] != INF) {
            ans = (ans + dp[i]) % mod;
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
    // cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}