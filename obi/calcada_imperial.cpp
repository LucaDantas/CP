#include<iostream>
#include<algorithm>

using namespace std;

int n, calc[510], ans = 0;

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> calc[i];
    }
    calc[n] = 0;
    for(int a = 0; a < n; a++)
    for(int b = 0; b < n; b++){
        int last = -1, local_ans = 0, n1 = calc[a], n2 = calc[b];
        for(int i = 0; i < n; i++){
            if(calc[i] == n1 || calc[i] == n2){
                if(calc[i] == last) continue;
                local_ans++;
                last = calc[i];
            } 
        }
        ans = max(ans, local_ans);
    }
    cout << ans << endl;
}