#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    const int mod = 1e9 + 7;
public:
    int maxValue(vector<int>& nums1, vector<int>& nums0) {
        int n = nums1.size();
        vector<string> s(n, "");
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < nums1[i]; j++) s[i] += '1';
            for(int j = 0; j < nums0[i]; j++) s[i] += '0';
        }

        sort(s.begin(), s.end(), [&](const string &a, const string &b) {
            int n = min(a.size(), b.size());
            for(int i = 0; i < n; i++) {
                if(a[i] != b[i]) {
                    if(a[i] > b[i]) return true;
                    else return false;
                }
            }
            return a.size() < b.size();
        });

        int res = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < s[i].size(); j++) {
                res = (res * 2 + (s[i][j] - '0')) % mod;
            }
        }
        
        return res;
    }
};