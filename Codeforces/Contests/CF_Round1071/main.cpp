#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

struct Query {
    int l, r;
};

void solve(int iTest) {
    int n, q; 
    cin >> n >> q;

    vector<Query> queries(q);
    for(int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
    }

    vector<int> ans(n + 1, 0);

    for(int b = 0; b < 19; b++) {
        int V = 1LL << b;
        int S = 1LL << (b + 1);
        
        vector<int> d_slope(n + S + 5, 0);
        vector<int> d_const(n + S + 5, 0);

        for(const auto& qry : queries) {
            int l = qry.l;
            int r = qry.r;

            int start_i = l - 1 + V;
            if(start_i > r) continue;

            int k = (r - start_i) / S;
            int end_i = start_i + k * S;
            int stop_i = end_i + S;

            d_slope[start_i] += V;
            d_slope[stop_i] -= V;

            int val_const = (1 - l) * V;
            d_const[start_i] += val_const;
            d_const[stop_i] -= val_const;
        }

        for(int i = 1; i <= n; i++) {
            if(i > S) {
                d_slope[i] += d_slope[i - S];
                d_const[i] += d_const[i - S];
            }
            ans[i] += d_slope[i] * i + d_const[i];
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
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