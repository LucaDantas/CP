#include<bits/stdc++.h>
using namespace std;

vector<int> hp;
vector<int> places;

int main(){
    int n, a, b, k, ans = 0;
    cin >> n >> a >> b >> k;
    hp.resize(n);
    for(int i = 0; i < n; i++){
        cin >> hp[i];
    }
    for(int i = 0; i < n; i++){
        while(hp[i] > a+b) hp[i]-=a+b;
        cout << hp[i] << ' ' << a << endl;
        if(hp[i] <= a) {ans++; cout << "OI" << endl;}
        else places.push_back(ceil( ( (float)hp[i] ) / (float)a )-1);
    }
    sort(places.begin(), places.end());
    for(int pt : places){
        if(pt < k) {
            ans++;
            k-=pt;
        }
        else break;
    }
    cout << ans << endl;
}