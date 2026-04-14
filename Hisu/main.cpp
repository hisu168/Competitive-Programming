#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

int n, a[N], pre[N], ans;

// fenwick tree 2d for range minimum query
struct FenwickTree2D {
    int n;
    vector<vector<int>> fenw;

    FenwickTree2D(int n) : n(n) {
        fenw.assign(n + 1, vector<int>(n + 1, LLONG_MAX));
    }

    void update(int x, int y, int val) {
        for(int i = x; i <= n; i += i & -i) {
            for(int j = y; j <= n; j += j & -j) {
                fenw[i][j] = min(fenw[i][j], val);
            }
        }
    }

    int get(int x, int y) {
        int res = LLONG_MAX;
        for(int i = x; i > 0; i -= i & -i) {
            for(int j = y; j > 0; j -= j & -j) {
                res = min(res, fenw[i][j]);
            }
        }
        return res;
    }
} fw(N);

void solve(int iTest) {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    pre[0] = 0;
    for(int i = 1; i <= n; i++) {
        prea[i] = prea[i - 1] + a[i];
    }

    int sum[N];
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    // p x
    // delta = x - a[p]
    a[p] = x;
    sum[p] = sum[p - 1] + x;
    for(int i = p; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    // compress pre array
    vector<int> compress(prea, prea + n + 1);
    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());

    int mn[N]; // mn[i] là min index trong đoạn giá trị [1, i]]
    for(int i = 1; i <= n; i++) {
        mn[pre[i]] = i;
    }
    mn[0] = 0;
    for(int i = 1; i <= n; i++) {
        pre[i] = lower_bound(compress.begin(), compress.end(), pre[i]) - compress.begin() + 1;
        // int pos = fw.get(prea[i]);
        // ans = max(ans, i - pos + 1);
        // fw.update(prea[i], preb[i], i);


        ans = max(ans, i - mn[pre[i]]);
        mn[pre[i]] = min(mn[pre[i]], i);

        for(int j = 1; j <= maxValue; j++) {
            mn[j] = min(mn[j], mn[j - 1]);
        }
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
    // cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}