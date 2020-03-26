#include<bits/stdc++.h>
using namespace std;

#define MAXN 200100
int t[MAXN], col[MAXN];

void solve(){
    int n, num = 1;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> t[i];
    }
    col[1] = 1;
    for(int i = 2; i < n; i++){
        if(t[i] == t[i-1]) col[i] = col[i-1];
        else{
            if(num == 1) num++;
            cout << 'o' << endl;
            if(col[i-1] == 1) col[i] == 2;
            else col[i] == 1;
        }
    }
    if(t[n] == t[n-1] && t[n] == t[1]) col[n] = col[n-1];
    else if(col[n-1] == col[1]){
        if(col[n-1] == 1) col[n] == 2;
        else col[n] == 1;
    }
    else{
        if(t[n] == t[n-1]) col[n] == col[n-1];
        else if(t[n] == t[1]) col[n] == col[1];
        else{
            num++;
            col[n] = 3;
        }
    }
    cout << num << endl;
    cout << col[1];
    for(int i = 2; i <= n; i++){
        cout << ' ' << col[i];
    }
    cout << endl;
}

int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}