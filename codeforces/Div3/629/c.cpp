#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n, cont = 0;
    cin >> n;
    string x, a = "", b = "";
    cin >> x;
    while(cont < n && x[cont] != '1'){
        if(x[cont] == '2'){
            a += '1';
            b +='1';
        }
        else{
            a += '0';
            b += '0';
        }
        cont++;
    }
    if(cont++ < n){
        a += '1';
        b += '0';
        while(cont < n){
            a += '0';
            b += x[cont++];
        }
    }
    cout << a << endl << b << endl;
}

int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}