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
    int n, m, p;
    cin >> n >> m >> p;

    // Tinh nghich dao cua m modulo p
    int inv_m = bpow(m, p - 2, p);

    // Precompute luuy thua cua inv_m: inv_m^0, inv_m^1...
    // Vi n <= 2000, dung vector la du
    vector<int> pw(n + 2);
    pw[0] = 1;
    for(int i = 1; i <= n + 1; ++i) {
        pw[i] = pw[i - 1] * inv_m % p;
    }

    int total_S = 0;
    int sum_diff = 0;

    // 1. Duyet tam tai cac vi tri le (tai chinh ky tu i)
    for(int i = 0; i < n; ++i) {
        // Ban kinh mo rong toi da
        int max_rad = min(i, n - 1 - i);

        int S_c = 0;
        int V_c = 0;

        for(int r = 0; r <= max_rad; ++r) {
            // Do dai = 2*r + 1, so cap canh = r
            int prob = pw[r];
            S_c = (S_c + prob) % p;

            // He so = 2 * (thu tu 1-based) - 1. O day thu tu la r+1 -> 2*(r+1)-1 = 2r+1
            int coeff = (2 * r + 1);
            V_c = (V_c + prob * coeff % p) % p;
        }

        total_S = (total_S + S_c) % p;

        // term = V_c - S_c^2
        int term = (V_c - S_c * S_c % p + p) % p;
        sum_diff = (sum_diff + term) % p;
    }

    // 2. Duyet tam tai cac vi tri chan (giua i va i+1)
    for(int i = 0; i < n - 1; ++i) {
        // Ban kinh mo rong
        int max_rad = min(i, n - 1 - (i + 1));

        int S_c = 0;
        int V_c = 0;

        for(int r = 0; r <= max_rad; ++r) {
            // Do dai = 2 + 2r, so cap canh = 1 + r
            int prob = pw[r + 1];
            S_c = (S_c + prob) % p;

            // He so = 2 * (thu tu) - 1. Thu tu la r+1 -> 2r+1
            int coeff = (2 * r + 1);
            V_c = (V_c + prob * coeff % p) % p;
        }

        total_S = (total_S + S_c) % p;

        // term = V_c - S_c^2
        int term = (V_c - S_c * S_c % p + p) % p;
        sum_diff = (sum_diff + term) % p;
    }

    // Ket qua = (Tong S)^2 + Tong(V_c - S_c^2)
    int ans = (total_S * total_S % p + sum_diff) % p;
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
    cin >> T; // Da uncomment dong nay vi input co T
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}

/**
**/
