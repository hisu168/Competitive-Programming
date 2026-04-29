#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

struct SegTri {
    int n;
    vector<int> st, lazy;

    SegTri(int _n) {
        n = _n;
        st.resize(4 * n + 5, 0);
        lazy.resize(4 * n + 5, 0);
    }

    void push(int id, int l, int r) {
        if(lazy[id] == 0) return;
        if(l != r) {
            st[id << 1] += lazy[id];
            lazy[id << 1] += lazy[id];
            st[id << 1 | 1] += lazy[id];
            lazy[id << 1 | 1] += lazy[id];
        }
        lazy[id] = 0;
    }

    void update(int id, int l, int r, int u, int v, int val) {
        push(id, l, r);
        if(v < l || r < u) return;
        if(u <= l && r <= v) {
            st[id] += val;
            lazy[id] += val;
            push(id, l, r);
            return;
        }

        int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v, val);
        update(id << 1 | 1, mid + 1, r, u, v, val);
        st[id] = min(st[id << 1], st[id << 1 | 1]);
    }

    int get(int id, int l, int r, int u, int v) {
        push(id, l, r);
        if(v < l || r < u) return 1e18;
        if(u <= l && r <= v) return st[id];

        int mid = (l + r) >> 1;
        return min(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
    }

    void debug(int id, int l, int r) {
        push(id, l, r);
        cout << id << ' ' << l << ' ' << r << ' ' << st[id] << ed;
        if(l == r) return;

        int mid = (l + r) >> 1;
        debug(id << 1, l, mid);
        debug(id << 1 | 1, mid + 1, r);
    }
};

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    SegTri seg(n);
    vector<int> cnt(n + 2, 0);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int cap = (a[i] == 0 ? -1 : (a[i] - 1) / 2);
        // cout << i << ' ' << cap << ed;

        if(a[i] < ans && cnt[a[i]] == 0) seg.update(1, 0, n, 0, a[i], 1);
        else seg.update(1, 0, n, 0, cap, 1);

        if(a[i] <= n) cnt[a[i]]++;
        // for(int j = 0; j <= n; j++) cout << cnt[j] << ' ';
        // cout << ed;

        while(ans <= n) {
            int val;
            if(cnt[ans] == 0) val = ans;
            else val = (ans == 0 ? -1 : (ans - 1) / 2);
            seg.update(1, 0, n, 0, val, -1);

            if(seg.get(1, 0, n, 0, ans) < 0) {
                seg.update(1, 0, n, 0, val, 1);
                break;
            }
            else ans++;
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