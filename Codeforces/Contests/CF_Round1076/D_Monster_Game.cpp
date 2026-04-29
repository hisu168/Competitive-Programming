#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    sort(a.begin(), a.end(), greater<int>());

    vector<int> pre(n + 2, 0);
    for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + b[i - 1];
    pre[n + 1] = 1e15;

    int ans = 0;
    for(int i = 0; i < n; i++) {
        int pos = upper_bound(pre.begin(), pre.end(), i + 1) - pre.begin() - 1;
        ans = max(ans, pos * a[i]);
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