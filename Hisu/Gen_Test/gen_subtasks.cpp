
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
mt19937_64 rng;

ll Rand(ll l, ll r) {
    uniform_int_distribution<ll> dist(l, r);
    return dist(rng);
}

template<class T>
T Pick(const vector<T>& v) {
    return v[(size_t)Rand(0, (ll)v.size() - 1)];
}

int chooseN(int lim) {
    int mode = (int)Rand(0, 5);
    if (mode == 0) return lim;
    if (mode == 1) return (int)Rand(1, min<ll>(lim, 10));
    if (mode == 2) return (int)Rand(1, min<ll>(lim, 100));
    if (mode == 3) return (int)Rand(1, min<ll>(lim, 1000));
    if (mode == 4) return (int)Rand(max<ll>(1, lim / 2), lim);
    return (int)Rand(1, lim);
}

int chooseK() {
    vector<int> cand = {
        0, 1, 2, 3, 5, 10, 20, 50, 100, 500, 1000,
        (int)Rand(0, 200000), 200000
    };
    return Pick(cand);
}

vector<int> genUniform(int n, const vector<int>& colors) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = Pick(colors);
    return a;
}

vector<int> genRuns(int n, const vector<int>& colors, int maxRun = 30) {
    vector<int> a;
    a.reserve(n);

    int last = -1;
    while ((int)a.size() < n) {
        int color = Pick(colors);
        if ((int)colors.size() > 1) {
            int guard = 0;
            while (color == last && guard < 10) {
                color = Pick(colors);
                guard++;
            }
        }

        int remain = n - (int)a.size();
        int len = (int)Rand(1, min(remain, maxRun));
        for (int i = 0; i < len; i++) a.push_back(color);
        last = color;
    }
    return a;
}

vector<int> genAlternating12(int n) {
    vector<int> a(n);
    int start = (int)Rand(1, 2);
    for (int i = 0; i < n; i++) a[i] = ((i & 1) ? 3 - start : start);
    return a;
}

vector<int> genPrefixNon3Suffix3(int n) {
    int j = (int)Rand(1, n); // 1 <= j <= n
    vector<int> a(n);

    vector<int> pref;
    if (Rand(0, 1)) pref = genUniform(j, {1, 2});
    else pref = genRuns(j, {1, 2}, 40);

    for (int i = 0; i < j; i++) a[i] = pref[i];
    for (int i = j; i < n; i++) a[i] = 3;
    return a;
}

vector<int> genGeneralPattern(int n) {
    int mode = (int)Rand(0, 4);
    if (mode == 0) return genUniform(n, {1, 2, 3});
    if (mode == 1) return genRuns(n, {1, 2, 3}, 50);
    if (mode == 2) {
        vector<int> a(n);
        int heavy = (int)Rand(1, 3);
        for (int i = 0; i < n; i++) {
            if (Rand(1, 100) <= 70) a[i] = heavy;
            else {
                vector<int> other;
                for (int c = 1; c <= 3; c++) if (c != heavy) other.push_back(c);
                a[i] = Pick(other);
            }
        }
        return a;
    }
    if (mode == 3) {
        vector<int> a(n);
        vector<int> p = {1, 2, 3};
        shuffle(p.begin(), p.end(), rng);
        for (int i = 0; i < n; i++) a[i] = p[i % 3];
        return a;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (i < n / 3) a[i] = 1;
        else if (i < 2 * n / 3) a[i] = 2;
        else a[i] = 3;
    }
    shuffle(a.begin(), a.end(), rng);
    return a;
}

void printCase(int n, int k, const vector<int>& a) {
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
}

// ---- validators: check the generated test really belongs to the requested subtask ----

void validateCommon(int n, int k, const vector<int>& a) {
    assert(1 <= n && n <= 200000);
    assert(0 <= k && k <= 200000);
    assert((int)a.size() == n);
    for (int x : a) assert(1 <= x && x <= 3);
}

void validateSubtask(int subtask, int n, int k, const vector<int>& a) {
    validateCommon(n, k, a);

    if (subtask == 1) {
        assert(n <= 500);
    } else if (subtask == 2) {
        assert(n <= 2000);
    } else if (subtask == 3) {
        for (int x : a) assert(x <= 2);
    } else if (subtask == 4) {
        assert(k == 0);
    } else if (subtask == 5) {
        int j = n;
        while (j >= 1 && a[j - 1] == 3) j--;
        // positions 1..j must be != 3, positions j+1..n must be 3
        assert(1 <= j && j <= n);
        for (int i = 0; i < j; i++) assert(a[i] != 3);
        for (int i = j; i < n; i++) assert(a[i] == 3);
    } else if (subtask == 6) {
        // Stronger-than-necessary construction:
        // we generate only colors 1 and 2, so color 3 has frequency 0
        // in every segment, hence it is always a least common color.
        for (int x : a) assert(x != 3);
    } else if (subtask == 7) {
        // no extra constraint
    } else {
        assert(false);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <subtask:1..7> <seed> [forced_n]\n";
        return 1;
    }

    int subtask = stoi(argv[1]);
    unsigned long long seed = stoull(argv[2]);
    rng.seed(seed);

    int n = -1, k = -1;
    vector<int> a;

    auto getForcedN = [&](int lim) -> int {
        if (argc >= 4) {
            int forced = stoi(argv[3]);
            assert(1 <= forced && forced <= lim);
            return forced;
        }
        return chooseN(lim);
    };

    if (subtask == 1) {
        n = getForcedN(500);
        k = chooseK();
        a = (Rand(0, 1) ? genUniform(n, {1,2,3}) : genRuns(n, {1,2,3}, 20));
    } else if (subtask == 2) {
        n = getForcedN(2000);
        k = chooseK();
        a = (Rand(0, 1) ? genUniform(n, {1,2,3}) : genRuns(n, {1,2,3}, 30));
    } else if (subtask == 3) {
        n = getForcedN(200000);
        k = chooseK();
        a = (Rand(0, 1) ? genUniform(n, {1,2}) : genRuns(n, {1,2}, 50));
    } else if (subtask == 4) {
        n = getForcedN(200000);
        k = 0;
        a = genGeneralPattern(n);
    } else if (subtask == 5) {
        n = getForcedN(200000);
        k = chooseK();
        a = genPrefixNon3Suffix3(n);
    } else if (subtask == 6) {
        n = getForcedN(200000);
        k = chooseK();
        // Sufficient stronger condition: do not use color 3 at all.
        if (Rand(0, 1)) a = genUniform(n, {1,2});
        else {
            if (Rand(0, 1)) a = genRuns(n, {1,2}, 40);
            else a = genAlternating12(n);
        }
    } else if (subtask == 7) {
        n = getForcedN(200000);
        k = chooseK();
        a = genGeneralPattern(n);
    } else {
        cerr << "Subtask must be in [1..7]\n";
        return 1;
    }

    validateSubtask(subtask, n, k, a);
    printCase(n, k, a);
    return 0;
}
