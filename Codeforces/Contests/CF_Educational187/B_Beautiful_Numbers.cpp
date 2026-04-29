#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    string x; cin >> x;

    int sum = 0;
    vector<int> cost;
    for(int i = 0; i < x.size(); i++) {
        sum += x[i] - '0';
        cost.push_back(x[i] - '0');
        if(i == 0) cost.back()--;
    }

    if(sum <= 9) {
        cout << 0 << ed;
        return;
    }

    sort(cost.rbegin(), cost.rend());

    int ans = 0;
    for(int c : cost) {
        sum -= c;
        ans++;
        if(sum <= 9) break;
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