#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

struct Friend {
    int id, x, y, z;
};

void solve(int iTest) {
    int n, m, k; cin >> n >> m >> k;

    vector<int> a(m);
    for(int &x : a) cin >> x;

    vector<Friend> s(n);
    for(int i = 0; i < n; i++) {
        cin >> s[i].x >> s[i].y >> s[i].z;
        s[i].id = i;
        k -= s[i].y;
    }

    sort(a.begin(), a.end(), greater<int>());
    sort(s.begin(), s.end(), [&](Friend a, Friend b) {
        return a.x > b.x;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> cost;
    int id = 0, avail = 0;

    for(int i = 0; i < n; i++) {
        pq.push(s[i].z - s[i].y);

        while(id < m && a[id] >= s[i].x) {
            avail++;
            id++;
        }
        
        if(pq.size() > avail) {
            cost.push_back(pq.top());
            pq.pop();
        }
    }

    sort(cost.begin(), cost.end());

    int ans = pq.size();

    for(int &c : cost) {
        if(k >= c) {
            k -= c;
            ans++;
        }
        else break;
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