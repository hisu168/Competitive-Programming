#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;
const int mod = 998244353;
const int INV2 = 499122177;

void solve(int iTest) {
    int n, a, x;
    cin >> n >> a >> x;

    long long n_mod = n % mod;
    long long a_mod = a % mod;
    long long x_mod = x % mod;

    cout << (n_mod + 1) % mod * (a_mod * 2 % mod + n_mod * x_mod % mod) % mod * INV2 % mod << ed;
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
