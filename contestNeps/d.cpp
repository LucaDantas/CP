#include<bits/stdc++.h>
using namespace std;

#define MAXN 110

int a[MAXN][MAXN];

int main(){
    int n, m, mx = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }   
    int l = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            l+=a[i][j];
        }
        mx = max(mx, l);
        l = 0;
    } 
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            l+=a[j][i];
        }
        mx = max(mx, l);
        l = 0;
    } 

    cout << mx << endl;
}