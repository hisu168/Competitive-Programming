#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, W; cin >> n >> W;
    vector<pair<int, int>> a(n + 2, {0, 0});
    int ans = 0, dem = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        ans = max(ans, a[i].second);
    }

    sort(a.begin() + 1, a.begin() + n + 1, [&](pair<int, int> &a, pair<int, int> &b) {
        return a.first < b.first;
    });

    vector<int> pre(n + 2, 0);
    for(int i = 1; i <= n; i++) {
        pre[i] = max(pre[i - 1], a[i].second);
    }

    for(int i = 1; i <= n; i++) {
        int pos = upper_bound(a.begin() + 1, a.begin() + i, make_pair(W - a[i].first, LLONG_MAX)) - a.begin() - 1;
        if(pos > 0) ans = max(ans, pre[pos] + a[i].second);
    }

    if(W % 3 == 0) {
        vector<int> s;
        for(int i = 1; i <= n; i++) {
            if(a[i].first * 3 == W) s.push_back(a[i].second);
        }
        sort(s.begin(), s.end(), greater<int>());
        int sum = 0;
        for(int i = 0; i < s.size() && i < 3; i++) {
            sum += s[i];
        }
        ans = max(ans, sum);
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