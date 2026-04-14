#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, mod = 1e9 + 7;

int bpow(int n, int m, int mod) {
    int res = 1;
    for(; m > 0; m >>= 1) {
        if(m & 1) res = res * n % mod;
        n = n * n % mod;
    }
    return res;
}

int fact[N], invFact[N];
void precompute() {
    fact[0] = 1;
    for(int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % mod;
    invFact[N - 1] = bpow(fact[N - 1], mod - 2, mod);
    for(int i = N - 2; i >= 0; i--) invFact[i] = invFact[i + 1] * (i + 1) % mod;
}

int nCr(int n, int r) {
    if(r > n || r < 0) return 0;
    return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
}

void solve(int iTest) {
    int n; cin >> n;
    vector<int> b(n + 2, 0);
    for(int i = 1; i <= n; i++) cin >> b[i];

    vector<int> cnt(30, 0);
    for(int i = n; i >= 1; i--) {
        int val = b[i];
        for(int j = 0; j < 30; j++) {
            if(cnt[j] > i) {
                val = (val - (1ll << j) % mod * nCr(cnt[j], i) % mod + mod) % mod;
            }
        }

        for(int j = 0; j < 30; j++) if(val >> j & 1) cnt[j] = i;
    }

    for(int i = 1; i <= n; i++) {
        int val = 0;
        for(int j = 0; j < 30; j++) if(cnt[j] >= i) val |= (1ll << j);
        cout << val << " ";
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

    precompute();

    int T = 1;
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}