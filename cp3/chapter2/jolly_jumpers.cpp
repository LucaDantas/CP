#include<bits/stdc++.h>
using namespace std;

bool solve(int n){
    bitset<3001> bs;
    int a, b;
    cin >> b;
    for(int i = 0; i < n-1; i++){
        cin >> a;
        if(abs(a-b) > n-1) return false;
        if(bs[abs(a-b)] == 0) bs[abs(a-b)] = 1;
        else return false;
        b = a;
    }
    return true;
}

int main(){
    int n;
    while(cin >> n){
        if(solve(n)) cout << "Jolly" << endl;
        else cout << "Not jolly" << endl;
    }
}