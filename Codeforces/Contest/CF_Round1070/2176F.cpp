#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 25, mod = 998244353;

int bpow(int n, int m) {
    int res = 1;
    for(; m > 0; m >>= 1) {
        if(m & 1) res = res * n % mod;
        n = n * n % mod;
    }
    return res;
}

int p[N];
void sieve(int n) {
    for(int i = 2; i <= n; i++) if(p[i] == 0) {
        for(int j = i; j <= n; j += i) {
            p[j]++;
        }
    }
}

void solve(int iTest) {
    int n, k; cin >> n >> k;
    vector<int> cnt(n + 2, 0), a(n + 2, 0);
    vector<vector<int>> c(10, vector<int> (n + 2, 0));
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    vector<int> pw(20, 0);
    for(int i = 0; i < 20; i++) pw[i] = bpow(i, k);//, cout << pw[i] << ed;

    for(int g = 1; g <= n; g++) {
        for(int j = g; j <= n; j += g) {
            c[p[j]][g] += cnt[j];
        }
    }

    // for(int i = 0; i <= 8; i++) for(int j = 1; j <= n; j++) cout << i << ' ' << j << ' ' << c[i][j] << ed;

    vector<int> mobi(n + 2, 0);
    int ans = 0;
    for(int u = 0; u <= 8; u++) {
        for(int v = u; v <= 8; v++) {
            for(int g = n; g >= 1; g--) {
                int ways = c[u][g] * c[v][g] % mod;

                for(int j = g * 2; j <= n; j += g) {
                    ways = (ways - mobi[j] + mod) % mod;
                }
                mobi[g] = ways;

                // cout << u << ' ' << v << ' ' << g << ' ' << p[g] << ' ' << ways << ed;
                int x = max(0ll, u + v - p[g]),
                    contri = ways * pw[x] % mod * (u != v ? 2 : 1) % mod;
                // cout << contri << ed;
                ans = (ans + contri) % mod;
            }
        }
    }

    // cout << ans << ed;
    for(int i = 1; i <= n; i++) {
        ans = (ans - pw[p[a[i]]] + mod) % mod;
    }
    ans = ans * bpow(2, mod - 2) % mod;
    
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

    sieve(N - 15);

    int T = 1;
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}