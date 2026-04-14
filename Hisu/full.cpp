// Chaiyo...
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 3e6 + 5;
int n, m, k;
int timer, Assign[N], vis[N];
vector<pair<int, int>> g[N];
vector<int> adj[N];
pair<int, int> edge[N];

int cnt = 0;

bool dfs(int u, int pa) {
    for(auto v : adj[u]) if(vis[v] != timer) {
        vis[v] = timer;

        if(Assign[v] == -1) {
            Assign[v] = u;
            Assign[u] = v;
            return true;
        }
        else {
            bool res = dfs(Assign[v], v);
            if(res == true) {
                Assign[v] = u;
                Assign[u] = v;
                return true;
            }
        }
    }
    return false;
}

void solve(int iTest){
    for(int i = 0; i <= m + n + 2; i++) {
        g[i].clear();
        adj[i].clear();
    }

    map<pair<int, int>, bool> mp;
    int tmp = 0;
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        if(u > v) swap(u, v);
        if(mp.find(make_pair(u, v)) != mp.end()) continue;

        mp.insert({make_pair(u, v), true});
        edge[++tmp] = {u, v};
        g[u].push_back({v, tmp});
        g[v].push_back({u, tmp});
    }
//    for(int i = 1; i <= n; i++) edge[i + m] = {i, i + n};
//    sort(edge + 1, edge + 1 + m + n);
//
//    for(int i = 1; i <= m + n; i++) cout << edge[i].first << ' ' << edge[i].second << ed;
//
//    for(int i = 1; i <= m; i++) {
//        for(int j = i + 1; j <= m; j++) {
//            if(edge[i].first != edge[j].first) break;
//
//            adj[i].push_back(j);
//            adj[j].push_back(i);
//        }
//    }

    for(int i = 1; i <= n; i++) {
        if(g[i].size() == 0) {
            adj[tmp + 1].push_back(tmp + 2);
            adj[tmp + 2].push_back(tmp + 1);
            tmp += 2;
            continue;
        }

        if(g[i].size() == 1) {
            ++tmp;
            adj[g[i][0].second].push_back(tmp);
            adj[tmp].push_back(g[i][0].second);
            continue;
        }

        for(int id1 = 0; id1 < g[i].size(); id1++) {
            for(int id2 = id1 + 1; id2 < g[i].size(); id2++) {
                adj[g[i][id1].second].push_back(g[i][id2].second);
                adj[g[i][id2].second].push_back(g[i][id1].second);
            }
        }
    }

//    for(int i = 1; i <= tmp; i++) cout << edge[i].first << ' ' << edge[i].second << ed;
//    for(int i = 1; i <= tmp; i++) {
//        cout << i << ": ";
//        for(int v : adj[i]) cout << v << ' ';
//        cout << ed;
//    }

    vector<int> vt;
    for(int i = 1; i <= tmp; i++) vt.push_back(i);
    shuffle(vt.begin(), vt.end(), rng);

    fill(Assign, Assign + tmp + 2, -1);
    int ans = 0;
    for(int i = 1; i <= tmp; i++) if(Assign[i] == -1) {
        timer++;
        vis[i] = timer;
        ans += dfs(i, 0);
    }

//    for(int i = 1; i <= tmp; i++) cout << i << ' ' << Assign[i] << ed;
//    cout << ans << ed;

    cout << (ans >= k);
}

#define TASK "main"

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    if(fopen(TASK ".inp","r")){
        freopen(TASK ".inp","r",stdin);
        freopen(TASK ".out","w",stdout);
    }
    else if(fopen("main.inp","r")){
        freopen("main.inp","r",stdin);
        freopen("main.out","w",stdout);
    }

//    int T = 1;
////    cin >> T;
//    for(int iTest = 1; iTest <= T; iTest++){
//        solve(iTest);
//    }
    while(cin >> n >> m >> k) solve(1);
}

/**
**/
