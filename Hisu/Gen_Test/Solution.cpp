#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, INF = 1e9;
int n, k, c[N];
int cnt[3][N];

struct BIT2D {
    int n;
    vector<vector<int>> fw;
    vector<vector<int>> nodes;

    BIT2D(int n) : n(n) {
        nodes.resize(n + 2);
        fw.resize(n + 2);
    }

    void add(int x, int y) {
        for(int i = x; i <= n; i += i & -i) {
            nodes[i].push_back(y);
        }
    }

    void build() {
        for(int i = 1; i <= n; i++) {
            sort(nodes[i].begin(), nodes[i].end());
            nodes[i].erase(unique(nodes[i].begin(), nodes[i].end()), nodes[i].end());
            fw[i].assign(nodes[i].size() + 2, INF);
        }
    }

    void update(int x, int y, int val) {
        for(int i = x; i <= n; i += i & -i) {
            int pos = upper_bound(nodes[i].begin(), nodes[i].end(), y) - nodes[i].begin();
            for(int j = pos; j <= nodes[i].size(); j += j & -j) {
                fw[i][j] = min(fw[i][j], val);
            }
        }
    }

    int query(int x, int y) {
        int res = INF;
        for(int i = x; i > 0; i -= i & -i) {
            int pos = upper_bound(nodes[i].begin(), nodes[i].end(), y) - nodes[i].begin();
            for(int j = pos; j > 0; j -= j & -j) {
                res = min(res, fw[i][j]);
            }
        }
        return res;
    }
};

struct Element {
    int u, v, w, i;
    bool operator<(const Element& other) const {
        if(u != other.u) return u < other.u;
        return i < other.i;
    }
};

int calc(int *a, int *b, int *c) {
    vector<Element> val;
    vector<int> compress;
    for(int i = 0; i <= n; i++) {
        val.push_back({a[i] - b[i], b[i] - c[i], a[i] - c[i], i});
        compress.push_back(val.back().v);
    }
    
    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());
    
    auto getID = [&](int val) -> int{
        return lower_bound(compress.begin(), compress.end(), val) - compress.begin() + 1;
    };
    
    sort(val.begin(), val.end());
    
    BIT2D fw2d(compress.size());
    for(int i = 0; i <= n; i++) {
        fw2d.add(getID(val[i].v), -val[i].w);
    }
    fw2d.build();
    
    int res = 0;
    for(int i = 0; i <= n; i++) {
        res = max(res, val[i].i - fw2d.query(getID(val[i].v), -val[i].w + k));
        fw2d.update(getID(val[i].v), -val[i].w, val[i].i);
    }
    return res;
}

void solve(int iTest) {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> c[i];

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            cnt[j][i] = cnt[j][i - 1];
        }
        cnt[c[i] - 1][i]++;
    }

    int ans = 0;
    vector<int> p = {0, 1, 2};
    do {
        ans = max(ans, calc(cnt[p[0]], cnt[p[1]], cnt[p[2]]));
    } while(next_permutation(p.begin(), p.end()));

    cout << ans;
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