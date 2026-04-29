#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    vector<int> cnt(3);
    int sz = 0;
    for(int i = 0; i < 3; i++) {
        cin >> cnt[i];
        sz += cnt[i];
    }

    string ans = "";
    int x = -1, y = -1, z = -1;

    for(int len = 0; len < sz; len++) {
        int res = -1;
        for(int i = 0; i < 3; i++) if(cnt[i] > 0 && i != x && i != z) {
            if(res != -1) {
                if(cnt[i] > cnt[res]) res = i;
                else if(cnt[i] == cnt[res] && i == y) res = i;
            }
            else res = i;
        }

        if(res == -1) break;
        
        if(res == 0) ans += 'R';
        else if(res == 1) ans += 'G';
        else ans += 'B';
        cnt[res]--;

        x = y;
        y = z;
        z = res;
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