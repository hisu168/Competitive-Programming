#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;
int n, k;

void solve(int iTest) {
    cin >> n >> k;

    if(k & 1) {
        for(int i = 1; i <= k; i++) cout << n << ' ';
        cout << ed;
        return;
    }

    vector<int> a(k);
    for(int i = 32; i >= 0; i--) {
        int cnt = 0;
        for(int &x : a) {
            if((x | (1ll << i)) <= n) {
                x |= (1ll << i);
                cnt++;
            }
        }

        if(n >> i & 1) {
            if(cnt & 1 ^ 1) {
                for(int &x : a) {
                    if(x >> i & 1) {
                        x ^= (1ll << i);
                        break;
                    }
                }
            }
        }
        else {
            if(cnt & 1) {
                for(int &x : a) {
                    if(x >> i & 1) {
                        x ^= (1ll << i);
                        break;
                    }
                }
            }
        }
    }

    for(int x : a) cout << x << ' ';
    cout << ed;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // #define TASK "main"
    // if(fopen(TASK ".inp", "r")) {
    //     freopen(TASK ".inp", "r", stdin);
    //     freopen(TASK ".out", "w", stdout);
    // }
    // else if(fopen("main.inp", "r")) {
    //     freopen("main.inp", "r", stdin);
    //     freopen("main.out", "w", stdout);
    // }

    int T = 1;
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}