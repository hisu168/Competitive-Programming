#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end(), [&](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        int n = factory.size(),
            m = robot.size();
        vector<vector<long long>> dp(n + 2, vector<long long> (m + 2, 1e15));
        for(int i = 0; i <= n; i++) dp[i][0] = 0;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                int x = factory[i - 1][0],
                    lim = factory[i - 1][1];
                long long sum = 0;

                for(int k = j; k >= max(1, j - lim + 1); k--) {
                    sum += abs(x - robot[k - 1]);
                    dp[i][j] = min(dp[i][j], dp[i - 1][k - 1] + sum);
                }

                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            }
        }

        return dp[n][m];
    }
};