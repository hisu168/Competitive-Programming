#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, mod = 998244353;

int bpow(int n, int m) {
    int res = 1;
    for(; m > 0; m >>= 1) {
        if(m & 1) res = res * n % mod;
        n = n * n % mod;
    }
    return res;
}

struct BIT {
    int n;
    vector<int> fw;

    BIT(int n) : n(n), fw(n + 5, 0) {}

    void update(int pos, int val) {
        for(int i = pos; i <= n; i += i & -i) fw[i] += val;
    }

    int query(int pos) {
        int res = 0;
        for(int i = pos; i > 0; i -= i & -i) res += fw[i];
        return res;
    }

    int get(int k) {
        int id = 0;
        for(int i = 20; i >= 0; i--) {
            int next = id + (1 << i);
            if(next <= n && fw[next] < k) {
                id = next;
                k -= fw[next];
            }
        }
        return id + 1;
    }
};

void solve(int iTest) {
    int m; cin >> m;
    vector<int> a(m), compress;
    for(int &x : a) {
        cin >> x;
        compress.push_back(x);
    }

    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());

    BIT cnt(compress.size()), sum(compress.size());
    for(int i = 1; i <= m; i++) {
        int val = a[i - 1];
        int pos = lower_bound(compress.begin(), compress.end(), val) - compress.begin() + 1;

        cnt.update(pos, 1);
        sum.update(pos, val);

        // cout << a[i - 1] << " " << pos << ed;

        if(i < 3) continue;

        int l = 1, r = i, ans = 2e18;
        while(l <= r) {
            int mid = l + r >> 1;

            // cout << mid << " " << l << " " << r << ed;

            int lVal = 0, rVal = 0;
            if(mid > 1) {
                int id = cnt.get(mid - 1);
                lVal = cnt.query(id - 1) * compress[id - 1] - sum.query(id - 1);
                // cout << cnt.query(id - 1) << " " << compress[id - 1] << " " << sum.query(id - 1) << ed;
            }

            if(mid < i) {
                int id = cnt.get(mid + 1);
                rVal = sum.query(compress.size()) - sum.query(id) - (cnt.query(compress.size()) - cnt.query(id)) * compress[id - 1];
                // cout << (cnt.query(compress.size()) - cnt.query(id)) << " " << compress[id - 1] << " " << (sum.query(compress.size()) - sum.query(id)) << ed;
            }

            ans = min(ans, max(lVal, rVal));

            // cout << ans << " " << lVal << " " << rVal << ed;

            if(lVal == rVal) break;
            else if(lVal > rVal) r = mid - 1;
            else l = mid + 1;
        }

        cout << ans % mod * bpow(i - 2, mod - 2) % mod << ed;
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