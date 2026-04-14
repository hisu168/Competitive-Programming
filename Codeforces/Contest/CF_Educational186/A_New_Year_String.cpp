#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    string s; cin >> s;

    for(int i = 0; i + 3 < n; i++) {
        if(s[i] == '2' && s[i + 1] == '0' && s[i + 2] == '2' && s[i + 3] == '6') {
            cout << 0 << ed;
            return;
        }
    }

    bool check = true;
    for(int i = 0; i + 3 < n; i++) {
        if(s[i] == '2' && s[i + 1] == '0' && s[i + 2] == '2' && s[i + 3] == '5') {
            check = false;
            break;
        }
    }

    if(check == true) cout << 0 << ed;
    else cout << 1 << ed;
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