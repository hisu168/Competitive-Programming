#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> s(2);
    for(int i = 0; i < n; i++) {
        s[a[i] % 2].push_back(a[i]);
    }

    if(is_sorted(a.begin(), a.end())) {
        cout << "YES" << ed;
        return;
    }
    else if(s[0].empty() || s[1].empty()) {
        cout << "NO" << ed;
        return;
    }

    sort(s[0].begin(), s[0].end());
    sort(s[1].begin(), s[1].end());
    // for(int &x : s[0]) cout << x << " ";
    // cout << ed;
    // for(int &x : s[1]) cout << x << " ";
    // cout << ed;

    int max[2] = {-1, -1};
    for(int &x : a) {
        if(x > s[x & 1 ^ 1].back() && x > max[x & 1]) max[x & 1] = x;
        if(x < s[x & 1 ^ 1][0] && x < max[x & 1]) {
            cout << "NO" << ed;
            return;
        }
    }

    cout << "YES" << ed;
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