#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, x; cin >> n >> x;
    
    vector<int> a(n + 2), b(n + 2), c(n + 2);
    int val = 0, mx = -1e16;
    
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        val += (b[i] - 1) * a[i];
        mx = max(mx, a[i] * b[i] - c[i]);
    }

    if(val >= x) {
        cout << 0 << ed;
        return;
    }

    if(mx <= 0) {
        cout << -1 << ed;
        return;
    }
    
    cout << (x - val + mx - 1) / mx << ed;
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