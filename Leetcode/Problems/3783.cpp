#include <cmath>
using namespace std;

class Solution {
public:
    int mirrorDistance(int n) {
        int revVal = 0, tmpVal = n;
        
        while(tmpVal > 0) {
            revVal = revVal * 10 + tmpVal % 10;
            tmpVal /= 10;
        }

        return abs(revVal - n);
    }
};