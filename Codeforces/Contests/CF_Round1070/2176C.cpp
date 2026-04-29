#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> odd, even;
    for(int &x : a) {
        if(x & 1) odd.push_back(x);
        else even.push_back(x);
    }

    if(odd.size() == 0) {
        for(int i = 1; i <= n; i++) cout << 0 << ' ';
        cout << ed;
        return;
    }

    sort(odd.begin(), odd.end(), greater<int> ());
    sort(even.begin(), even.end(), greater<int> ());

    vector<int> pre(n + 2, 0);
    for(int i = 1; i <= even.size(); i++) {
        pre[i] = pre[i - 1] + even[i - 1];
    }

    for(int k = 1; k <= n; k++) {
        int val = max(1ll, k - (int) even.size());
        if(val & 1 ^ 1) val++;

        if(val <= odd.size() && val <= k) cout << odd[0] + pre[k - val] << ' ';
        else cout << 0 << ' ';
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