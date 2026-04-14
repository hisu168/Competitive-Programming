#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 5e5 + 5;
int n, q;
string t[N], s[N];

namespace subtask1 {
    bool check() {
        int len = 0;
        for(int i = 0; i < n; i++) len += t[i].size();
        for(int i = 0; i < q; i++) len += s[i].size();
        return len <= 1000;
    }

    void solve() {
        for(int i = 0; i < q; i++) {
            int cnt = 0;
            for(int j = 0; j < n; j++) {
                if(t[j].find(s[i]) != string::npos) cnt++;
            }
            cout << cnt << ed;
        }
    }
}

namespace subtask2 {
    void solve() {
        for(int i = 0; i < q; i++) {
            int cnt = 0;
            if(t[0].find(s[i]) != string::npos) cnt = 1;
            cout << cnt << ed;
        }
    }
}

namespace subtask3 {
    void solve() {
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            if(t[j].find(s[0]) != string::npos) cnt++;
        }
        cout << cnt << ed;
    }
}

namespace subtask4 {
    const int BLOCK = 600;
    int ans[N];

    struct TrieNode {
        int child[26];
        vector<int> qr;
        
        void clear() {
            memset(child, 0, sizeof(child));
            qr.clear();
        }
    } trie[N];
    
    int cntNodes = 0, last[N];

    void add(const string &s, int id) {
        int u = 0;
        for(char c : s) {
            int v = c - 'a';
            if(trie[u].child[v] == 0) {
                trie[u].child[v] = ++cntNodes;
                trie[cntNodes].clear();
            }
            u = trie[u].child[v];
        }
        trie[u].qr.push_back(id);
    }

    void solve() {
        vector<int> bigQ;
        
        trie[0].clear();
        for(int i = 0; i < q; i++) {
            if(s[i].size() > BLOCK) bigQ.push_back(i);
            else add(s[i], i);
        }

        memset(last, -1, sizeof(last));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < t[i].size(); j++) {
                int u = 0;
                for(int k = j; k < t[i].size(); k++) {
                    if(k - j + 1 > BLOCK) break; 
                    
                    int c = t[i][k] - 'a';
                    if(trie[u].child[c] == 0) break;
                    
                    u = trie[u].child[c];
                    
                    if(trie[u].qr.size() == 0) continue;

                    for(int id : trie[u].qr) if(last[id] != i) {
                        ans[id]++;
                        last[id] = i;
                    }
                }
            }
        }

        for(int id : bigQ) {
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                if(t[i].find(s[id]) != string::npos) cnt++;
            }
            ans[id] = cnt;
        }

        for(int i = 0; i < q; i++) cout << ans[i] << ed;
    }
}

void solve(int iTest) {
    cin >> n >> q;
    
    for(int i = 0; i < n; i++) cin >> t[i];
    for(int i = 0; i < q; i++) cin >> s[i];

    if(subtask1::check()) subtask1::solve();
    else if(n == 1) subtask2::solve();
    else if(q == 1) subtask3::solve();
    else subtask4::solve();
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