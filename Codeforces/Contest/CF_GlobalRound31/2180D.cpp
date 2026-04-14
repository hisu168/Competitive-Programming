#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, INF = 1e15;

void solve(int iTest) {
    int n;
    cin >> n;
    vector<int> x(n);
    for(int i = 0; i < n; i++) cin >> x[i];

    if(n < 2) {
        cout << 0 << ed;
        return;
    }

    vector<int> d(n, INF);
    for(int i = 0; i < n - 1; i++) {
        d[i] = x[i + 1] - x[i];
    }

    int l = 0, u = INF, ans = 0;

    for(int i = 0; i < n - 1; i++) {
        u = min(u, d[i]);

        int x = d[i] - u, y = d[i] - l;

        bool check = false;
        if(x < min(d[i + 1], y)) {
            check = true;
        }

        if(check == true) {
            ans++;
            l = x;
            u = y;
        }
        else {
            u = y;
            l = 0;
        }
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