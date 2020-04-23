#include<bits/stdc++.h>
using namespace std;

#define MAXN 1100

long long a[MAXN], f[MAXN];

int main(){
    int n, k, m;
    cin >> n >> k >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> f[i];
    }
    for(int i = n+1; i <= k; i++){
        f[i] = 0;
        for(int j = 1; j <= n; j++){
            f[i] += (f[i-j]*a[j]) % m;
            f[i] = (f[i]) % m;
        }
    }
    cout << f[k] << endl;
}