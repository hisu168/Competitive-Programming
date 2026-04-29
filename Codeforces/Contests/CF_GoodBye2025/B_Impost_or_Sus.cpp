#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    string r; cin >> r;

    int ans = 0, n = r.size();

    if(r[0] == 'u') {
        r[0] = 's';
        ans++;
    }

    if(r.back() == 'u') {
        r.back() = 's';
        ans++;
    }

    for(int i = 0; i < n; i++) if(r[i] == 'u') {
        int j = i;
        while(i < n && r[i] == 'u') i++;
        
        ans += (i - j) / 2;
        i--;
    }

    cout << ans << endl;
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