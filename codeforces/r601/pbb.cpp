#include<iostream>
#include<vector>

using namespace std;

void solve(){
    int n, m, cost = 0, mm = 0, s = 1000000000, pm = 0, ps = 0;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        cost+= 2*a[i];
    }
    if(m < n || n == 2) cout << -1 << endl;
    else{
        cout << cost << endl;
        for(int i = 1; i < n; i++){
            cout << i << ' ' << i+1 << endl;
        }
        cout << n << ' ' << 1 << endl;
    }
}

int main(){
    int t;
    cin >> t;
    while(t--) solve();
}