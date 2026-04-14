#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

static mt19937_64 rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count());

int RandInt(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

template<class T>
T Pick(const vector<T>& v) {
    return v[(size_t)RandInt(0, (int)v.size() - 1)];
}

struct BIT2D {
    int n;
    vector<vector<int>> fw, nodes;
    static constexpr int INF = 1e9;

    BIT2D(int n = 0) : n(n), fw(n + 2), nodes(n + 2) {}

    void addPoint(int x, int y) {
        for (int i = x; i <= n; i += i & -i) nodes[i].push_back(y);
    }

    void build() {
        for (int i = 1; i <= n; i++) {
            auto &v = nodes[i];
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            fw[i].assign((int)v.size() + 2, INF);
        }
    }

    void update(int x, int y, int val) {
        for (int i = x; i <= n; i += i & -i) {
            int pos = (int)(upper_bound(nodes[i].begin(), nodes[i].end(), y) - nodes[i].begin());
            for (int j = pos; j <= (int)nodes[i].size(); j += j & -j) fw[i][j] = min(fw[i][j], val);
        }
    }

    int query(int x, int y) {
        int res = INF;
        for (int i = x; i > 0; i -= i & -i) {
            int pos = (int)(upper_bound(nodes[i].begin(), nodes[i].end(), y) - nodes[i].begin());
            for (int j = pos; j > 0; j -= j & -j) res = min(res, fw[i][j]);
        }
        return res;
    }
};

struct Element {
    int u, v, w, idx;
    bool operator<(const Element& other) const {
        if (u != other.u) return u < other.u;
        return idx < other.idx;
    }
};

int calcOne(const vector<int>& A, const vector<int>& B, const vector<int>& C, int n, int k) {
    vector<Element> val;
    vector<int> compress;
    val.reserve(n + 1);
    compress.reserve(n + 1);

    for (int i = 0; i <= n; i++) {
        int u = A[i] - B[i];
        int v = B[i] - C[i];
        int w = A[i] - C[i];
        val.push_back({u, v, w, i});
        compress.push_back(v);
    }

    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());
    auto getID = [&](int x) {
        return (int)(lower_bound(compress.begin(), compress.end(), x) - compress.begin()) + 1;
    };

    sort(val.begin(), val.end());
    BIT2D fw((int)compress.size());
    for (int i = 0; i <= n; i++) fw.addPoint(getID(val[i].v), -val[i].w);
    fw.build();

    int res = 0;
    for (int i = 0; i <= n; i++) {
        res = max(res, val[i].idx - fw.query(getID(val[i].v), -val[i].w + k));
        fw.update(getID(val[i].v), -val[i].w, val[i].idx);
    }
    return res;
}

int solveCase(const vector<int>& c, int k) {
    int n = (int)c.size() - 1;
    vector<int> cnt0(n + 1, 0), cnt1(n + 1, 0), cnt2(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cnt0[i] = cnt0[i - 1];
        cnt1[i] = cnt1[i - 1];
        cnt2[i] = cnt2[i - 1];
        if (c[i] == 1) cnt0[i]++;
        else if (c[i] == 2) cnt1[i]++;
        else cnt2[i]++;
    }

    array<const vector<int>*, 3> arr = {&cnt0, &cnt1, &cnt2};
    vector<int> p = {0, 1, 2};
    int ans = 0;
    do {
        ans = max(ans, calcOne(*arr[p[0]], *arr[p[1]], *arr[p[2]], n, k));
    } while (next_permutation(p.begin(), p.end()));
    return ans;
}

bool validateSub6(const vector<int>& a) {
    int n = (int)a.size() - 1;
    vector<int> p1(n + 1, 0), p2(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        p1[i] = p1[i - 1];
        p2[i] = p2[i - 1];
        if (a[i] == 1) p1[i]++;
        else if (a[i] == 2) p2[i]++;
        else { p1[i]--; p2[i]--; }
    }

    int mx1 = INT_MIN / 4, mx2 = INT_MIN / 4;
    for (int i = 1; i <= n; i++) {
        if (i - 3 >= 0) {
            mx1 = max(mx1, p1[i - 3]);
            mx2 = max(mx2, p2[i - 3]);
            if (p1[i] < mx1 || p2[i] < mx2) return false;
        }
    }
    return true;
}

// Max-density strong construction for subtask 6.
// Base pattern 12123 (or its color-swapped twin 21213) has one color-3 every 5 positions,
// which is essentially the densest possible shape under subtask 6.
vector<int> genStrongSub6(int n, int mode) {
    string base = (mode % 2 == 0 ? "12123" : "21213");
    int shift = mode % 5;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = base[(shift + i - 1) % 5] - '0';
    return a;
}

int chooseN(int id) {
    if (id <= 10) return RandInt(20, 300);
    if (id <= 20) return RandInt(500, 4000);
    if (id <= 35) return RandInt(6000, 30000);
    if (id <= 44) return RandInt(40000, 90000);
    return RandInt(120000, 180000);
}

int chooseK(int id, int n) {
    vector<int> cand = {0, 1, 2, 3, 5, 10, 20, 50, 100, 500, 1000, n / 20, n / 10, n / 5, n / 2, n, 200000};
    int k = Pick(cand);
    k = max(0, min(200000, k));
    if (id % 10 == 0) k = 0;
    if (id % 10 == 1) k = 1;
    if (id % 10 == 2) k = 2;
    if (id >= 46 && RandInt(0, 1)) k = 200000;
    return k;
}

void writeCase(const string& path, int n, int k, const vector<int>& a) {
    ofstream fout(path);
    fout << n << ' ' << k << '\n';
    for (int i = 1; i <= n; i++) fout << a[i] << (i == n ? '\n' : ' ');
}

int main(int argc, char* argv[]) {
    uint64_t seed = 20260331ULL;
    if (argc >= 2) seed = strtoull(argv[1], nullptr, 10);
    rng.seed(seed);

    fs::create_directories("test");
    for (int id = 1; id <= 50; id++) {
        int n = chooseN(id);
        int k = chooseK(id, n);
        vector<int> a = genStrongSub6(n, id);
        if (!validateSub6(a)) {
            cerr << "Invalid generated test at id=" << id << '\n';
            return 1;
        }

        int ans = solveCase(a, k);
        ostringstream name;
        name << setw(2) << setfill('0') << id;
        string base = "test/" + name.str();
        writeCase(base + ".inp", n, k, a);
        ofstream fout(base + ".out");
        fout << ans << '\n';
        cerr << "Generated " << base << ".inp/.out | n=" << n << " k=" << k << '\n';
    }
    return 0;
}
