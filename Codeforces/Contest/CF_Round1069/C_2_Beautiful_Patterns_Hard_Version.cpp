// Chaiyo...
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

int bpow(int n, int m, int mod) {
    int res = 1;
    for(; m > 0; m >>= 1) {
        if(m & 1) res = res * n % mod;
        n = n * n % mod;
    }
    return res;
}

void solve(int iTest) {
    int n, m, p; cin >> n >> m >> p;

    int inv_m = bpow(m, p - 2, p);

    vector<int> pw(n + 1), prefS(n + 1), prefV(n + 1);

    pw[0] = prefS[0] = prefV[0] = 1;
    for(int i = 1; i < n; i++) {
        pw[i] = pw[i - 1] * inv_m % p;
        prefS[i] = (prefS[i - 1] + pw[i]) % p;
        prefV[i] = (prefV[i - 1] + pw[i] * (2 * i + 1) % p) % p;
    }

    int res = 0, sum = 0;
    for(int i = 0; i < n; i++) {
        int mx = min(i, n - 1 - i),
            s = prefS[mx], v = prefV[mx];

        res = (res + s) % p;
        sum = (sum + (v - s * s % p + p) % p) % p;
    }
    for(int i = 0; i < n - 1; i++) {
        int mx = min(i, n - 1 - (i + 1)),
            s = prefS[mx] * inv_m % p,
            v = prefV[mx] * inv_m % p;

        res = (res + s) % p;
        sum = (sum + (v - s * s % p + p) % p) % p;
    }

    int ans = (res * res % p + sum) % p;
    cout << ans << ed;
}

#define TASK "main"

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

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

/**
**/