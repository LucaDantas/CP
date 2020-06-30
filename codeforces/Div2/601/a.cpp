#include<iostream>

using namespace std;

void solve(){
    int a, b, cont = 0, rest = 0;
    cin >> a >> b;
    rest = abs(b - a);
    if(rest >= 5) cont = rest/5;
    rest = rest%5;
    if(rest == 4 || rest == 3) cont+=2;
    else if(rest > 0) cont++;
    cout << cont << endl;
}

int main(){
    int t;
    cin >> t;
    while(t--) solve();
}