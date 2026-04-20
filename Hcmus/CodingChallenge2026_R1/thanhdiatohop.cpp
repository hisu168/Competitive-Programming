#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5, mod = 1e9 + 7, mod2 = 500000003;

// CTDL biểu diễn đồng dư thức, gồm số dư và modulo
struct Congruence {
    long long rem;
    long long mod;

    Congruence(long long __rem, long long __mod) {
        rem = __rem;
        mod = __mod;
        if (mod) {
            rem %= mod;
            if (rem < 0) {
                rem += mod;
            }
        }
    }
};

// Hàm trả về ƯCLN của a và b, biến đổi x, y thoả mãn ax + by = gcd(a, b)
long long extEuclid(long long a, long long b,
                    long long &x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long q = a / b;
    long long r = a - b * q;
    long long x1 = 0, y1 = 0;
    long long d = extEuclid(b, r, x1, y1);
    x = y1;
    y = x1 - q * y1;
    return d;
}

// Tính nghịch đảo modulo bằng cách giải phương trình Diophantus
long long invMod(long long num, long long mod) {
    long long inv = 0;
    long long y = 0;
    extEuclid(num, mod, inv, y);
    inv %= mod;
    if (inv < 0) {
        inv += mod;
    }
    return inv;
}

// Nghiệm của phương trình là một đồng dư thức mà, đúng không?
Congruence solveCongruenceEqSet(vector <Congruence>& eqSet) {
    Congruence sol(0, 1);

    for (int i = 0; i < (int)eqSet.size(); i++) {
        sol.mod *= eqSet[i].mod;
    }

    vector <long long> p;
    vector <long long> pInv;
    for (int i = 0; i < (int)eqSet.size(); i++) {
        p.push_back(sol.mod / eqSet[i].mod);
        pInv.push_back(invMod(p[i], eqSet[i].mod));
    }

    for (int i = 0; i < (int)eqSet.size(); i++) {
        long long prod = 1;
        prod = prod * p[i] % sol.mod;
        prod = prod * pInv[i] % sol.mod;
        prod = prod * eqSet[i].rem % sol.mod;
        sol.rem += prod;
    }
    sol.rem %= sol.mod;

    return sol;
}
// Mình lụm code CRT từ VNOI Wiki nhé <3

int bpow(int n, int m, int mod) {
    int res = 1;
    for(; m > 0; m >>= 1) {
        if(m & 1) res = res * n % mod;
        n = n * n % mod;
    }
    return res;
}

void solve(int iTest) {
    int n, x; cin >> n >> x;

    vector<int> fact(n + 2, 0), invFact(n + 2, 0);
    fact[0] = 1;
    for(int i = 1; i <= n + 1; i++) fact[i] = fact[i - 1] * i % mod2;
    invFact[n + 1] = bpow(fact[n + 1], mod2 - 2, mod2);
    for(int i = n; i >= 0; i--) invFact[i] = invFact[i + 1] * (i + 1) % mod2;

    auto C = [&](int n, int k) -> int {
        if(k > n || k < 0) return 0;
        return fact[n] * invFact[k] % mod2 * invFact[n - k] % mod2;
    };

    int sum = 0;
    for(int i = 0; i <= n; i++) {
        int a = C(n, i),
            b = (n - __builtin_popcount(n)) - (i - __builtin_popcount(i)) - (n - i - __builtin_popcount(n - i));
        // cout << a << ' ' << b << ed;
        b = (b == 0);

        vector<Congruence> eqSet = {Congruence(a, mod2), Congruence(b, 2)};
        Congruence res = solveCongruenceEqSet(eqSet);

        sum = (sum + bpow(x, res.rem, mod)) % mod;
        cout << sum << ' ';
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
    // cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}