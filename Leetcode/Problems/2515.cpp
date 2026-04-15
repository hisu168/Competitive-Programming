#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int res = -1;
        for(int i = 0; i < words.size(); i++) if(words[i] == target) {
            if(res == -1) res = min(abs(i - startIndex), (int)words.size() - abs(i - startIndex));
            else res = min(res, min(abs(i - startIndex), (int)words.size() - abs(i - startIndex)));
        }
        return res;
    }
};