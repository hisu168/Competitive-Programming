#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int l, r;
    cin >> l >> r;

    if(l == r) {
        cout << 0 << ed;
        return;
    }

    int k = min(__builtin_ctzll(l), __builtin_ctzll(r + 1));
    
    auto check = [&](int val) -> bool {
        return val > 0 && __builtin_popcountll(val + 1) == 1;
    };
    int base = check((l >> k) ^ (r >> k)) ? 2 : 1;

    cout << ((1ll << k) * base) - 1 << ed;
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