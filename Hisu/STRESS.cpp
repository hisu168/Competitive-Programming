#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ed "\n"
int n, m;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randint(int l, int r){
    if (l > r) return 0;
    return uniform_int_distribution <int> (l, r) (rng);
}

int randint2(int l, int r){
    return l + rand() % (r - l + 1);
}

#define INP "main"
#define TASK "main"
#define TASK2 "trau"

signed main(){
    int Tests = 100;
    for(int iTest = 1; iTest <= Tests; iTest++){
        srand(time(NULL));
        ofstream inp(INP ".inp");

        auto gen = [&](int n_max) -> void {
            int n = randint(n_max - n_max / 5, n_max);
            inp << n << ed;
            for(int i = 1; i <= n; i++) {
                inp << randint(1, 3) << " ";
            }
        };

        // inp << 1 << ed;
        gen(6);

        inp.close();

        system(TASK ".exe");
        system(TASK2 ".exe");
        if(system("fc main.out main.ans") != 0){
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}
/*
*/
