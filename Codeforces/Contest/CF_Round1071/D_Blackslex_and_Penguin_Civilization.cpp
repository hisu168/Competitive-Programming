#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

vector<int> build(int n) {
    if(n == 1) return {1, 0};
    vector<int> s = build(n - 1);

    vector<int> res;

    for(int x : s) res.push_back(x << 1 | 1);
    for(int i = 0; i < (1 << (n - 1)); i++) res.push_back(i << 1);

    return res;
}

void solve(int iTest) {
    int n; cin >> n;
    
    vector<int> ans = build(n);
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
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

    int T = 1;
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}