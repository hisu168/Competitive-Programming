#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> p(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    int st = -1, en = -1;
    for(int i = 1; i <= n; i++) {
        if(n - p[i] + 1 != i) {
            st = i;
            break;
        }
    }

    if(st == -1) {
        for(int i = 1; i <= n; i++) cout << p[i] << " ";
        cout << ed;
        return;
    }

    for(int i = st; i <= n; i++) {
        if(en == -1 || p[i] > p[en]) {
            en = i;
        }
    }

    reverse(p.begin() + st, p.begin() + en + 1);
    for(int i = 1; i <= n; i++) cout << p[i] << " ";
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

    int T = 1;
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}