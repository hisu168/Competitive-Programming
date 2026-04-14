#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 1e6 + 5;
int p[N];
vector<int> primes;

void sieve() {
    for(int i = 2; i < N; i++) {
        if(p[i] == 0) {
            p[i] = i;
            primes.push_back(i);
        }
        for(int j = 0; j < (int)primes.size() && primes[j] <= p[i] && i * primes[j] < N; j++) {
            p[i * primes[j]] = primes[j];
        }
    }
}

void solve(int iTest) {
    int n; cin >> n;

    for(int i = 0; i < n; i++) {
        cout << primes[i] * primes[i + 1] << ' ';
    }
    cout << ed;
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