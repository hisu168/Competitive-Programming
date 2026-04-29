#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int s, m; cin >> s >> m;

    auto check = [&](int n, int s, int m) {
        int res = s;
        for(int i = 60; i >= 0; i--) if(m >> i & 1) {
            int x = min(n, res >> i);
            res -= x * (1LL << i);
        }
        return res == 0;
    };

    if(check(s, s, m) == false) {
        cout << -1 << ed;
        return;
    }

    int l = 1, r = s, ans = s;
    while(l <= r) {
        int mid = l + r >> 1;

        if(check(mid, s, m) == true) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
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