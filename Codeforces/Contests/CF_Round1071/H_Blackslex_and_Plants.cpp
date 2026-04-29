#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n, q; 
    cin >> n >> q;
    
    vector<pair<int, int>> queries(q);
    for(int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    vector<int> ans(n + 2, 0);
    vector<int> slope(n + 5, 0), d(n + 5, 0);

    for(int b = 0; b < 19; b++) {
        int val = 1ll << b, step = 1ll << (b + 1);

        for(auto [l, r] : queries) {
            int st = l - 1 + val;
            if(st > r) continue;

            int k = (r - st) / step;
            int en = st + k * step,
                stop = en + step;

            slope[st] += val;
            d[st] += -val * (l - 1);
            
            if(stop <= n) {
                slope[stop] -= val;
                d[stop] -= -val * (l - 1);
            }
        }

        for(int i = 1; i <= n; i++) {
            if(i >= step) {
                slope[i] += slope[i - step];
                d[i] += d[i - step];
            }
            ans[i] += slope[i] * i + d[i];
        }

        for(int i = 1; i <= n; i++) {
            slope[i] = 0;
            d[i] = 0;
        }
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
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