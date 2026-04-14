#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

void solve(int iTest) {
    int n; cin >> n;
    vector<int> a(n), b(n), c(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    for(int &x : c) cin >> x;

    int cntAB = 0, cntBC = 0;

    for(int j = 0; j < n; j++) {
        bool check = true;
        for(int i = 0; i < n; i++) {
            if(a[i] >= b[(i + j) % n]) {
                check = false;
                break;
            }
        }
        cntAB += check;

        check = true;
        for(int i = 0; i < n; i++) {
            if(b[i] >= c[(i + j) % n]) {
                check = false;
                break;
            }
        }
        cntBC += check;
    }

    cout << n * cntAB * cntBC << ed;
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