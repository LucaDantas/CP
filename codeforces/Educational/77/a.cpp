#include<iostream>
#include<algorithm>
 
using namespace std;
 
int main(){
    int n;
    cin >> n;
    while(n--){
        int r, s, sum=0;
        cin >> r >> s;
        int prices[r];
        fill(prices, prices+r, s/r);
        for(int i = 0; i < s%r; i++){
            prices[i]++;
        }
        for(int i : prices){
            sum += i*i;
        }
        cout << sum << endl;
    }
}