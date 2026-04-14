#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int a, b; cin >> a >> b;

    int odd = 0, even = 0, mx = 0;
    
    for(int i = 1; i < 32; i++) {
        if(i & 1) odd += (1ll << (i - 1));
        else even += (1ll << (i - 1));

        if((odd <= a && even <= b) || (odd <= b && even <= a)) mx = i;
        else break;
    }

    cout << mx << ed;
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