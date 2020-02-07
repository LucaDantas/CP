#include<bits/stdc++.h>
using namespace std;

bool solve(int n) {
    bitset<3010> sv;
    bool broke = false;
    vector<int> numb(n);
    for(int i = 0; i < n; i++){
        cin >> numb[i];
    }
    for(int i = 1; i < n; i++){
        int d = abs(numb[i] - numb[i-1]);
        if(d == 0 || d>n-1 || sv.test(d)) return false;
        else sv.set(abs(numb[i] - numb[i-1]));
    }
    return true;
}

int main(){
    int n;
    while(cin >> n && n){
        solve(n)? cout << "Jolly" << endl : cout << "Not Jolly" <<endl;
    }
}