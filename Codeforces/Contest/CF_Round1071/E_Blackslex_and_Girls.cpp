#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, x, y; cin >> n >> x >> y;
    string s; cin >> s;
    vector<int> p(n + 2, 0);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    if(x + y < accumulate(p.begin() + 1, p.begin() + n + 1, 0ll)) {
        cout << "NO" << ed;
        return;
    }

    int valX = 0, valY = 0;
    bool zero = false, one = false;

    for(int i = 1; i <= n; i++) {
        if(s[i - 1] == '0') {
            zero = true;
            valX += p[i] / 2 + 1;
        }
        else {
            one = true;
            valY += p[i] / 2 + 1;
        }
    }

    if(x < valX || y < valY) {
        cout << "NO" << ed;
        return;
    }

    if(zero == true && one == true) {
        cout << "YES" << ed;
    }
    else if(zero == true) {
        if(x >= y + n) cout << "YES" << ed;
        else cout << "NO" << ed;
    }
    else {
        if(y >= x + n) cout << "YES" << ed;
        else cout << "NO" << ed;
    }
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