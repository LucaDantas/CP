#include<bits/stdc++.h>
using namespace std;

#define MAXN 100100

void solve(){
    int n, k, b1 = 0, b2;
    cin >> n >> k;
    while(++b1 < k){
        k -= b1;
    } 
    b1++;
    b2 = k;
    for(int i = n; i >= 1; i--){
        if(i == b1 || i == b2){
            cout << 'b';
        } 
        else cout << 'a';
    }
    cout << endl;
}

int main(){
    int t;
    cin >> t;
    for(int j = 0; j < t; j++){
        solve();
    }
}