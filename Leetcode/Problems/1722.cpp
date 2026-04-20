#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct DSU {
        int n;
        vector<int> lab;

        DSU() : n(0) {}
        DSU(int _n) : n(_n) {
            lab.assign(n + 2, -1);
        }

        int root(int n) {
            return lab[n] < 0 ? n : lab[n] = root(lab[n]);
        }

        bool unite(int x, int y) {
            x = root(x); y = root(y);
            if(x != y) {
                if(lab[x] > lab[y]) swap(x, y);
                lab[x] += lab[y];
                lab[y] = x;
                return true;
            }
            return false;
        }
    };

    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        DSU dsu(n);

        for(int i = 0; i < allowedSwaps.size(); i++) {
            int a = allowedSwaps[i][0],
                b = allowedSwaps[i][1];
            dsu.unite(a, b);
        }

        vector<vector<int>> s(n + 2);
        for(int i = 0; i < n; i++) {
            s[dsu.root(i)].push_back(i);
        }

        int mx = max(*max_element(source.begin(), source.end()), *max_element(target.begin(), target.end()));
        vector<int> cnt(mx + 2, 0);
        int res = 0;

        for(int i = 0; i < n; i++) {
            int r = dsu.root(i);

            for(auto &pos : s[r]) cnt[source[pos]]++;

            for(auto &pos : s[r]) {
                if(cnt[target[pos]] > 0) cnt[target[pos]]--;
                else res++;
            }

            for(auto &pos : s[r]) cnt[source[pos]] = 0;

            s[r].clear();
        }

        return res;
    }
};