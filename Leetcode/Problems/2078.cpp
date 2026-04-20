#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int res = 0;
        for (int i = 0; i + 1 < colors.size(); ++i) {
            for (int j = i + 1; j < colors.size(); ++j) {
                if(colors[i] != colors[j]) res = max(res, j - i);
            }
        }

        return res;
    }
};