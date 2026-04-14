#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> dp(n + 2, 1e15);
    vector<bool> check(n + 2, false);
    for(int &x : a) dp[x] = check[x] = 1;

    vector<vector<int>> divs(n + 2);
    for(int i = 1; i <= n; i++) {
        for(int j = i * 2; j <= n; j += i) {
            divs[j].push_back(i);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int d : divs[i]) if(check[d] == true) {
            dp[i] = min(dp[i], dp[i / d] + 1);
        }
    }

    for(int i = 1; i <= n; i++) cout << (dp[i] == 1e15 ? -1 : dp[i]) << ' ';
    cout << ed;
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