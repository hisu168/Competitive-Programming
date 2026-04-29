#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, INF = 1e16;

struct SegTri {
    int n;
    vector<int> st;
    
    SegTri(int _n) : n(_n) {
        st.assign(n * 4 + 5, INF);
    }

    void update(int id, int l, int r, int k, int val) {
        if(r < k || l > k) return;
        if(l == r) {
            st[id] = val;
            return;
        }

        int mid = l + r >> 1;
        if(k <= mid) update(id << 1, l, mid, k, val);
        else update(id << 1 | 1, mid + 1, r, k, val);

        st[id] = min(st[id << 1], st[id << 1 | 1]);
    }

    int query(int id, int l, int r, int u, int v) {
        if(r < u || l > v) return INF;
        if(u <= l && r <= v) return st[id];
        int mid = l + r >> 1;
        return min(query(id << 1, l, mid, u, v), query(id << 1 | 1, mid + 1, r, u, v));
    }
};

void solve(int iTest) {
    int n, q; cin >> n >> q;
    vector<int> a(n + 2, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegTri st(n);
    for(int i = 1; i <= n; i++) {
        st.update(1, 1, n, i, a[i]);
    }

    while(q--) {
        int type; cin >> type;

        if(type == 1) {
            int pos, x;
            cin >> pos >> x;
            st.update(1, 1, n, pos, x);
            a[pos] = x;
        }
        else {
            int l, r;
            cin >> l >> r;
            int low = 0, high = r - l;
            bool check = false;

            while(low <= high) {
                int mid = low + high >> 1;
                int mn = st.query(1, 1, n, l, l + mid);

                if(mn == mid) {
                    check = true;
                    break;
                }
                else if(mn > mid) low = mid + 1;
                else high = mid - 1;
            }

            if(check == true) cout << 1 << ed;
            else cout << 0 << ed;
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
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}