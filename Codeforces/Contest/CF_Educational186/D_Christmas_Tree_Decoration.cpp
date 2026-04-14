#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, mod = 998244353;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n + 1);
    for(int &x : a) cin >> x;
    
    int sum = accumulate(a.begin(), a.end(), 0ll);
    int q = sum / n,
        r = sum % n;
    int cnt = 0;

    // cout << q << ' ' << r << ed;
    
    for(int i = 1; i <= n; i++) {
        // cout << i << ' ' << a[i] << ' ' << cnt << ed;
        if(a[i] > q + 1 || cnt > r) {
            cout << 0 << ed;
            return;
        }
        
        cnt += (a[i] == q + 1);
    }

    // cout << cnt << ed;

    int ans = 1;
    for(int i = 0; i < cnt; i++) ans = ans * (r - i) % mod;
    for(int i = 1; i <= n - cnt; i++) ans = ans * i % mod;

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