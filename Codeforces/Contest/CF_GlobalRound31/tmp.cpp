#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> x(n);
        for (int i = 0; i < n; i++) cin >> x[i];

        if (n <= 1) {
            cout << 0 << "\n";
            continue;
        }

        vector<long long> d(n - 1);
        for (int i = 0; i < n - 1; i++) d[i] = x[i + 1] - x[i];

        const long long INF = (long long)4e18;
        long long L = 0, U = INF; // r_i in (L, U)
        long long ans = 0;

        for (int i = 0; i < n - 1; i++) {
            long long di = d[i];

            // must have some r_i < di
            U = min(U, di);
            // (L >= U) would mean impossible, but should not happen with this greedy

            // try to make edge i tangent: r_{i+1} = di - r_i
            long long Lt = max(0LL, di - U);
            long long Ut = di - L;
            bool ok = (Lt < Ut); // non-empty open interval

            if (ok && i + 1 < n - 1) {
                long long dnext = d[i + 1];
                ok = (Lt < min(Ut, dnext)); // need some r_{i+1} < dnext
            }

            if (ok) {
                ans++;
                L = Lt; U = Ut;
            } else {
                // make this edge non-tangent, maximize future freedom
                U = di - L;
                L = 0;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
