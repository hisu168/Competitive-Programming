#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

typedef long long ll;
#define ed "\n"
#define int long long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randint(int l, int r){
    if (l > r) return l;
    return uniform_int_distribution <int> (l, r) (rng);
}

// ĐƯỜNG DẪN ĐẾN FILE MAIN.EXE
const string SOLVER_PATH = R"(C:\Workspace\CP\Base\main.exe)"; 
const string TEST_DIR = "test";

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    if (fs::exists(TEST_DIR)) fs::remove_all(TEST_DIR);
    fs::create_directory(TEST_DIR);
    cout << "Da lam sach thu muc " << TEST_DIR << endl;

    function<string(int n, int sz)> convert = [&](int n, int sz){
        string res = to_string(n);
        while(res.size() < sz) res = "0" + res;
        return res;
    };

    int Tests = 50; 
    for(int iTest = 1; iTest <= Tests; iTest++){
        string fileNameBase = TEST_DIR + "/" + convert(iTest, 2);
        string inFile = fileNameBase + ".inp";
        string outFile = fileNameBase + ".out";
        
        ofstream inp(inFile);

        // --- LOGIC SINH TEST BÀI 4: KHO HANG ---
        auto gen = [&]() -> void {
            int n;
            // 50% test đầu n <= 10^3, 50% sau n <= 10^5
            if (iTest <= 25) n = randint(10, 1000);
            else n = randint(1001, 100000);

            inp << n << ed;

            // Số cạnh tối đa 2*10^5 theo đề
            int m_limit = 200000;
            // Với n nhỏ thì m không quá n*(n-1)
            if (n <= 1000) m_limit = min(m_limit, (int)(n * (n - 1) / 2)); 

            int type = randint(1, 3); 
            // Type 1: Random thuần (dễ ra 1 TPLT mạnh lớn)
            // Type 2: Rời rạc (Nhiều cụm riêng biệt) -> Test khả năng đếm đủ số cụm
            // Type 3: DAG (Các cụm nối nhau) -> Test khả năng lọc bậc vào > 0

            vector<pair<int,int>> edges;

            if (type == 1) {
                // Random m cạnh
                int m = randint(n / 2, m_limit); 
                // Đảm bảo không quá dày để chạy nhanh
                if (m > 200000) m = 200000;

                for(int i = 0; i < m; i++) {
                    int u = randint(1, n);
                    int v = randint(1, n);
                    if (u != v) edges.push_back({u, v});
                }
            } 
            else if (type == 2) {
                // Chia thành k cụm (ví dụ 5-20 cụm)
                int k = randint(5, 20);
                vector<int> roots;
                // Tạo cạnh nội bộ trong từng cụm để nó thành 1 cục
                for (int i = 1; i <= n; i++) {
                    // Nối i với 1 thằng ngẫu nhiên trong cụm của nó hoặc tạo vòng
                    // Đơn giản: nối i -> ngẫu nhiên, xác suất cao
                    if (randint(0, 1)) {
                         int v = randint(1, n); 
                         edges.push_back({i, v});
                    }
                }
            }
            else {
                // Type 3: Tạo 1 đường line hoặc cây các node để test bậc vào
                // Nối i -> i+1 để tạo chuỗi dài
                for (int i = 1; i < n; i++) {
                    edges.push_back({i, i+1});
                    // Thêm nhiễu (back-edge) ít thôi để không tạo thành 1 vòng lớn
                    if (randint(1, 100) == 1) edges.push_back({i+1, i}); 
                }
                // Thêm một số cạnh random hướng về phía trước (i -> j với i < j)
                int extra = randint(0, n);
                for (int k = 0; k < extra; k++){
                    int u = randint(1, n-1);
                    int v = randint(u+1, n);
                    edges.push_back({u, v});
                }
            }

            // Ghi ra file
            // Shuffle cạnh để không bị lộ pattern
            shuffle(edges.begin(), edges.end(), rng);
            // Giới hạn lại số cạnh nếu lỡ sinh quá nhiều (dù logic trên đã chặn)
            if (edges.size() > 200000) edges.resize(200000);

            for (auto p : edges) {
                inp << p.first << " " << p.second << ed;
            }
        };
        // ---------------------------------------

        gen();
        inp.close();

        string cmd = "\"" + SOLVER_PATH + "\" < " + inFile + " > " + outFile;
        int ret = system(cmd.c_str());
        if (ret != 0 || !fs::exists(outFile) || fs::file_size(outFile) == 0) {
            cerr << "Solver failed at test " << iTest << "\n";
            return 0;
        }
        
        cout << "Generated test " << iTest << ": Done." << endl;
    }
    cout << "Hoan tat sinh " << Tests << " test!" << endl;
}