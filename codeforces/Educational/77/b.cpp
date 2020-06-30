#include<iostream>
#include<algorithm>
 
using namespace std;
 
int main(){
    int n;
    cin >> n;
    while(n--){
                int a, b;
        cin >> a >> b;
        if(a > b) swap(a,b);
        if((a+b)%3 == 0 && a*2 >= b)cout << "YES" << endl;
        else cout << "NO" << endl; 
    }
}