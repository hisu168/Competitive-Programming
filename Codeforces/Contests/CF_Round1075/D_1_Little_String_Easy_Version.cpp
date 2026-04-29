#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, mod = 1e9 + 7;

void solve(int iTest) {
    int n, c; cin >> n >> c;
    string s; cin >> s;

    if(s.back() == '0') {
        cout << -1 << ed;
        return;
    }

    int ans = 1, checkMod = 1, cnt = 0;
    for(int i = 0; i + 1 < n; i++) {
        ans = ans * (s[i] == '1' ? 2 : cnt) % mod;
        checkMod = checkMod * (s[i] == '1' ? 2 : cnt) % c;

        cnt++;
    }

    if(checkMod == 0) cout << -1 << ed;
    else cout << ans << ed;
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