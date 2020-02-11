#include<bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> f;

int main(){
    int n, k, m;
    cin >> n >> k >> m;
    a.resize(n);
    f.resize(k+1);
    fill(f.begin(), f.end(), 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> f[i];
    }
    for(int i = n; i <= k; i++){
        for(int j = 0; j < n; j++){
            f[i] += a[j]*f[i-j];    
        }
        f[i] = f[i]%m;
        cout << f[i] << endl;
    }
    cout << "Massa" << endl; 
    cout << f[k] << endl;
}