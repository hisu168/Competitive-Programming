#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 4e5 + 5, mod = 998244353;
int n, blockSize[N], sz[N];
vector<int> g[N];
bool check[N]; 

int bpow(int n, int m) {
    int res = 1;
    for(; m > 0; m >>= 1) {
        if(m & 1) res = res * n % mod;
        n = n * n % mod;
    }
    return res;
}

void preDfs(int u, int pa) {
    sz[u] = 1;
    for(int v : g[u]) if(v != pa) {
        preDfs(v, u);
        sz[u] += sz[v];
    }
    if(sz[u] & 1 ^ 1) check[u] = true;
}

void dfs(int u, int pa, int root) {
    if(u == 1 || check[u]) root = u;
    blockSize[root]++;
    
    for(int v : g[u]) if(v != pa) {
        dfs(v, u, root);
    }
}

void solve(int iTest) {
    cin >> n;
    
    for(int i = 0; i <= n + 2; i++) {
        g[i].clear();
        blockSize[i] = sz[i] = check[i] = 0;
    }

    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    preDfs(1, 0);
    dfs(1, 0, 1);

    vector<int> bl;
    for(int i = 2; i <= n; i++) if(check[i] == true) bl.push_back(blockSize[i]);

    if(bl.size() == 0) {
        cout << 1 << ed;
        return;
    }

    int ans = blockSize[1];
    for(int i = 1; i < bl.size(); i++) ans = ans * i % mod;

    int val = 1, invSum = 0;
    for(int s : bl) {
        ans = ans * s % mod * s % mod;
        invSum = (invSum + bpow(s, mod - 2)) % mod;
    }
    ans = (ans * invSum) % mod;

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