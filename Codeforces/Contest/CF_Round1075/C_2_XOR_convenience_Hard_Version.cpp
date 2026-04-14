#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;

    vector<int> p;
    for(int i = 1; i <= n; i++) p.push_back(i);

    bool found = false;
    do {
        bool check = true;
        for(int i = 0; i + 1 < n; i++) {
            bool kt = false;
            for(int j = i; j < n; j++) {
                if(p[i] == (p[j] ^ (i + 1))) {
                    kt = true;
                    break;
                }
            }

            if(kt == false) {
                check = false;
                break;
            }
        }

        if(check == true) {
            for(int i = 0; i < n; i++) {
                cout << p[i] << " ";
            }
            cout << ed;
            found = true;
        }
    } while(next_permutation(p.begin(), p.end()));

    if(found == false) {
        cout << -1 << ed;
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