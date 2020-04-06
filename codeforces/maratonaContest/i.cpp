#include<iostream>
#include<cmath>
using namespace std;

int main(){
    long long n, r, p = 0;
    cin >> n;
    long long w = n*(n+1)/2;
    for(int i = 0; i < n; i++){
        cin >> r;
        p+=r;
    }
    if(w-p < 0) cout << p-w << endl;
    else cout << w-p << endl;
}