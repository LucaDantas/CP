#include<iostream>
#include<unordered_map>
using namespace std;

unordered_map<int, int> let;

void solve(){
    int n, a, minm= 1000000;
    cin >> n;
    let.clear();
    for(int i = 0; i < n; i++){
        cin >> a;
        if(let[a] == 0) let[a] = i+1;
        else {minm = min(minm, i+1 - let[a]); let[a] = i+1;}
    }
    if(minm != 1000000) cout << minm+1 << endl;
    else cout << -1 << endl;
}

int main(){
    int t;
    cin >> t;
    while(t--) solve();
}