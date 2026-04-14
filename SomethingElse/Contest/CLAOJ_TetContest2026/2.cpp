#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n), f(n);
    
    map<int, int> cntA, cntF;

    for(int i = 0; i < n; i++) {
        cin >> a[i] >> f[i];
        cntA[a[i]]++;
        cntF[f[i]]++;
    }

    for(auto [key, val] : cntA) {
        if(val + cntF[key] > n) {
            cout << -1 << ed;
            return;
        }
    }

    int res = 0, mx = 0;
    map<int, int> bad;

    for(int i = 0; i < n; i++) {
        if(a[i] != f[i]) continue;

        res++;
        bad[a[i]]++;
        mx = max(mx, bad[a[i]]);
    }
    
    cout << max((res + 1) / 2, mx) << ed;
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