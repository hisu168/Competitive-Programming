#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

struct Elf {
    int id, x;
};

void solve(int iTest) {
    int n, m;
    cin >> n >> m;
    vector<Elf> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].x;
        a[i].id = i + 1;
    }

    sort(a.begin(), a.end(), [&](Elf &u, Elf &v) {
        return u.x < v.x;
    });

    if(m == 0) {
        int sum = 0;
        for(int i = 0; i < n - 1; i++) sum += a[i].x;

        if(sum >= a[n - 1].x) {
            sum = 0;
            for(int i = 0; i < n - 2; i++) sum += a[i].x;

            int k = 0;
            while(k < n - 2 && sum >= a[n - 1].x) {
                sum -= a[k].x;
                k++;
            }

            cout << n - 1 << ed;
            for(int i = 0; i < k; i++) cout << a[i].id << ' ' << a[i + 1].id << ed;
            for(int i = k; i < n - 1; i++) cout << a[i].id << ' ' << a[n - 1].id << ed;
        }
        else cout << -1 << ed;
        return;
    }

    if(n < m * 2) {
        cout << -1 << ed;
        return;
    }
    
    vector<pair<int, int>> ops;

    for(int i = 0; i < n - 2 * m; i++) ops.push_back({a[i].id, a[i + 1].id});
    for(int i = 0; i < m; i++) ops.push_back({a[n - m + i].id, a[n - 2 * m + i].id});

    cout << ops.size() << ed;
    for(auto [x, y] : ops) {
        cout << x << ' ' << y << ed;
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