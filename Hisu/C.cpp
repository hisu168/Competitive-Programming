// Chaiyo...
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 1e3 + 5;
int n, m, k;
int e[N][N];

void solve(int iTest){
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            e[i][j] = 0;
        }
    }

    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        e[u][v] = e[v][u] = 1;
    }

    for(int mask = 1; mask < (1 << n); mask++) if(__builtin_popcount(mask) >= k) {
        int kt = true;
        for(int i = 0; i < n; i++) if(mask >> i & 1) {
            for(int j = i; j < n; j++) if(mask >> j & 1) {
                if(e[i][j] == 1) {
                    kt = false;
                    break;
                }
            }
        }

        if(kt == true) {
            cout << 1;
            return;
        }
    }

    cout << 0;
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
