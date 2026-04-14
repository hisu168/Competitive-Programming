#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ed "\n"
#define int long long

const int N = 2e5 + 5;

// Hàm hỗ trợ thực hiện truy vấn và flush dữ liệu
int ask(const vector<int>& indices) {
    if (indices.empty()) return 0;
    cout << "? " << indices.size();
    for (int idx : indices) cout << " " << idx;
    cout << endl; // endl thực hiện flush buffer
    int res;
    cin >> res;
    if (res == -1) exit(0); 
    return res;
}

void solve(int iTest) {
    int n;
    if (!(cin >> n)) return;
    int total_len = 2 * n + 1;

    // 1. Tìm vị trí thứ ba (p3) của giá trị xuất hiện 3 lần
    int low = 1, high = total_len, p3 = total_len;
    while (low <= high) {
        int mid = (low + high) / 2;
        vector<int> s;
        for (int j = 1; j <= mid; ++j) s.push_back(j);
        
        // Nếu số lượng phần tử lẻ mà kết quả chẵn (hoặc ngược lại)
        // Nghĩa là cả 3 vị trí p1, p2, p3 đều nằm trong đoạn [1, mid]
        if (ask(s) % 2 != mid % 2) {
            p3 = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    // 2. Tìm vị trí thứ hai (p2) trong khoảng [1, p3-1]
    low = 1, high = p3 - 1;
    int p2 = p3 - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        vector<int> s;
        for (int j = 1; j <= mid; ++j) s.push_back(j);
        s.push_back(p3); // Luôn bao gồm p3
        
        if (ask(s) % 2 != (mid + 1) % 2) {
            p2 = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    // 3. Tìm vị trí thứ nhất (p1) trong khoảng [1, p2-1]
    low = 1, high = p2 - 1;
    int p1 = p2 - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        vector<int> s;
        for (int j = 1; j <= mid; ++j) s.push_back(j);
        s.push_back(p2); // Bao gồm p2
        s.push_back(p3); // Bao gồm p3
        
        if (ask(s) % 2 != (mid + 2) % 2) {
            p1 = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    // In kết quả cuối cùng
    cout << "! " << p1 << " " << p2 << " " << p3 << endl;
}

signed main() {
    // Lưu ý: Đối với bài Interactive, cin.tie(0) vẫn ổn nếu dùng endl
    // Nhưng nếu dùng "\n" thì phải cout.flush() thủ công.
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    #define TASK "main"
    if(fopen(TASK ".inp", "r")) {
        freopen(TASK ".inp", "r", stdin);
        freopen(TASK ".out", "w", stdout);
    }
    else if(fopen("main.inp", "r")) {
        freopen("main.inp", "r", stdin);
        freopen("main.out", "w", stdout);
    }

    int T = 1;
    cin >> T; // Đã mở comment để đọc số lượng test cases
    for(int iTest = 1; iTest <= T; iTest++) {
        solve(iTest);
    }
    return 0;
}