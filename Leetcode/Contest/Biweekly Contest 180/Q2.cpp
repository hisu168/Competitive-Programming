#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countDigitOccurrences(vector<int>& nums, int digit) {
        int res = 0;
        for(int &val : nums) {
            while(val > 0) {
                if(val % 10 == digit) res++;
                val /= 10;
            }
        }
        return res;
    }
};