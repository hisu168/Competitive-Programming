#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> pos;
        vector<long long> arr(nums.size(), 0);

        for(int i = 0; i < nums.size(); i++) pos[nums[i]].push_back(i);

        for(auto [val, vp] : pos) if(vp.size() > 1) {
            long long sumRight = 0;
            long long sumLeft = 0;
            for(int i = 1; i < vp.size(); i++) sumRight += vp[i];

            arr[vp[0]] = sumRight - (long long)vp[0] * (vp.size() - 1);
            for(int i = 1; i < vp.size(); i++) {
                sumRight -= vp[i];
                sumLeft += vp[i - 1];
                arr[vp[i]] = ((long long)vp[i] * i - sumLeft) + (sumRight - (long long)vp[i] * (vp.size() - i - 1));
            }
        }

        return arr;
    }
};