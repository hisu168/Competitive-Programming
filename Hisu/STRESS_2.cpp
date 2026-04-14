#include <bits/stdc++.h>
using namespace std;

//uoc gi dau doi tuyen
//uoc gi len Expert

mt19937 chim(chrono::steady_clock::now().time_since_epoch().count());

int range(int l, int r){
    return l + chim() % (r - l + 1);
}

const int maxN = (int) 10;
const int maxS = (int) 10;

void maketest(){
    ofstream inp("main.inp");
    int n = range(2, maxN);
    int k = range(1, n / 2);
    inp << n << " " << k << "\n";
    for(int i = 1; i <= n; i++){
        inp << range(1, maxS) << " ";
    }
    inp << "\n";
    for(int i = 2; i <= n; i++){
        inp << range(1, i - 1) << " " << i << "\n";
    }
    inp.close();
}

int main(){
    for(int test = 1; test <= 500; test++){
        maketest();
        system("A.exe");
        system("trau.exe");
        if(system("fc main.out main.ans")){
            cout << "Test " << test << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << test << ": CORRECT!\n";
    }
}
