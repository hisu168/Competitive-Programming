#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n + 2, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int sum = 0;
    for(int i = 1; i < n ; i++) sum += abs(a[i] - a[i + 1]);

    int ans = sum;
    for(int i = 1; i <= n; i++) {
        int cur = sum;
        if(i > 1) cur -= abs(a[i] - a[i - 1]);
        if(i < n) cur -= abs(a[i] - a[i + 1]);
        if(i > 1 && i < n) cur += abs(a[i - 1] - a[i + 1]);
        ans = min(ans, cur);
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