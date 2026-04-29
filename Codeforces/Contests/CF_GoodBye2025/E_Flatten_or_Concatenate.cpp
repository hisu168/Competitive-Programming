#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int unsigned long long

const int N = 2e5 + 5;

int ask(int l, int r) {
    cout << "? " << l << " " << r << endl;
    int res; cin >> res;
    // if(res == -1) assert(false);
    return res;
}

void answer(int ans) {
    cout << "! " << ans << endl;
    return;
}

void solve(int iTest) {
    int n; cin >> n;

    int l = 1, r = n;
    int curSum = ask(l, r);

    while(l < r) {
        if(curSum == r - l + 1) {
            answer(1);
            return;
        }

        int res = curSum / 2, id = -1;

        int low = l, high = r - 1;
        while(low <= high) {
            int mid = low + high >> 1,
                val = ask(l, mid);
            
            if(val == res) {
                id = mid;
                break;
            }
            else if(val < res) low = mid + 1;
            else high = mid - 1;
        }

        int lenA = id - l + 1,
            lenB = r - id;

        if(lenA < lenB) r = id;
        else l = id + 1;
        
        curSum = res;
    }

    answer(curSum);
}

signed main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);

    // #define TASK "main"
    // if(fopen(TASK ".inp", "r")) {
    //     freopen(TASK ".inp", "r", stdin);
    //     freopen(TASK ".out", "w", stdout);
    // }
    // else if(fopen("main.inp", "r")) {
    //     freopen("main.inp", "r", stdin);
    //     freopen("main.out", "w", stdout);
    // }

    int T = 1;
    cin >> T;
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
}