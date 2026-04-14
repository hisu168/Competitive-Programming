#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, m; cin >> n >> m;

    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    int lim = *max_element(b.begin(), b.end()),
        lcm = 1;
    for(int &x : a) {
        int g = __gcd(lcm, x);

        if(lcm / g > lim / x) {
            lcm = lim + 5;
            break;
        }

        lcm = lcm / g * x;
    }

    int cnta = 0, cntb = 0;
    if(lcm <= lim) {
        for(int &x : b) cnta += (x % lcm == 0);
    }

    vector<bool> check(lim + 5, false);
    for(int &x : a) if(x <= lim && check[x] == false) {
        for(int j = x; j <= lim; j += x) check[j] = true;
    }

    for(int &x : b) if(check[x] == false) cntb++;

    if(cnta + (m - cnta - cntb) % 2 > cntb) cout << "Alice" << ed;
    else cout << "Bob" << ed;
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