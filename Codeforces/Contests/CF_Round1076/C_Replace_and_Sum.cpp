#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, q; cin >> n >> q;
    vector<int> a(n + 2, 0), b(n + 2, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    for(int i = n; i >= 1; i--) {
        a[i] = max({a[i], a[i + 1], b[i]});
    }

    vector<int> pre(n + 2, 0);
    for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];

    while(q--) {
        int l, r; cin >> l >> r;
        cout << pre[r] - pre[l - 1] << ' ';
    }
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