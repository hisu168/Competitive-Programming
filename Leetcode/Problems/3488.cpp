#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int maxVal = *max_element(nums.begin(), nums.end());
        int n = nums.size();

        vector<vector<int>> pos(maxVal + 1);
        for(int i = 0; i < n; i++) pos[nums[i]].push_back(i);

        vector<int> ans;
        for(int& p : queries) {
            int val = nums[p],
                m = pos[val].size();

            if(pos[val].size() <= 1) {
                ans.push_back(-1);
                continue;
            }

            int id = lower_bound(pos[val].begin(), pos[val].end(), p) - pos[val].begin();
            int res = 1e9;

            res = min(res, abs(p - pos[val][(id - 1 + m) % m]));
            res = min(res, n - abs(p - pos[val][(id - 1 + m) % m]));

            res = min(res, abs(p - pos[val][(id + 1) % m]));
            res = min(res, n - abs(p - pos[val][(id + 1) % m]));

            ans.push_back(res);
        }

        return ans;
    }
};