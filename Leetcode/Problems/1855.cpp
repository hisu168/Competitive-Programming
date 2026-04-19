#include <vector>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i, j;
        for(i = 0, j = 0; i < nums1.size() && j < nums2.size(); j++) {
            if(nums1[i] > nums2[j]) {
                i++;
            }
        }

        if(i == j) return 0;
        return j - i - 1;
    }
};