#include<bits/stdc++.h>
 
using namespace std;
 
int main(){
    int n;
    cin >> n;
    while(n--){
        int r,b,k;
        cin >> r >> b >> k;
        if(r > b) swap(r,b);
        int g = __gcd(r,b);
        r /= g;
        b /= g;
        if(ceil( ((double)b-1) / ((double)r) ) >= k) cout << "REBEL" << endl;
        else cout << "OBEY" << endl;
    }
    return 0;
}
