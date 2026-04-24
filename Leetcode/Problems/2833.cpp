#include <string>
#include <cmath>
using namespace std;

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int curPos = 0, cnt_ = 0;
        for(char &c : moves) {
            if(c == 'L') curPos--;
            else if(c == 'R') curPos++;
            else cnt_++;
        }

        return max(abs(curPos + cnt_), abs(curPos - cnt_));
    }
};