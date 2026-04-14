#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        vector<int> p(2e5 + 5, 0), primes;
        p[0] = p[1] = 1;
        for(int i = 2; i < 2e5; i++) {
            if(p[i] == 0) {
                primes.push_back(i);
                for(long long j = (long long) i * i; j < 2e5; j += i) {
                    p[j] = i;
                }
            }
        }

        int res = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(i & 1) {
                while(p[nums[i]] == 0) {
                    nums[i]++;
                    res++;
                }
            }
            else {
                int val = *lower_bound(primes.begin(), primes.end(), nums[i]);
                res += val - nums[i];
            }
        }
        
        return res;
    }
};