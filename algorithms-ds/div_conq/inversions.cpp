#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000

vector<int> vec;

int count(vector<int> &v){
    int inv = 0;
    if(v.size() == 1) return 0;
    vector<int> u1, u2;
    for(int i = 0; i < v.size()/2; i++){
        u1.push_back(v[i]);
    }
    for(int i = v.size()/2; i < v.size(); i++){
        u2.push_back(v[i]);
    }
    inv += count(u1) + count(u2);
    int ini1 = 0, ini2 = 0;
    u1.push_back(INF);
    u2.push_back(INF);
    for(int i = 0; i < v.size(); i++){
        if(u1[ini1] <= u2[ini2]){
            v[i] = u1[ini1];
            ini1++;
        }
        else {
            v[i] = u2[ini2];
            ini2++;
            inv += u1.size() - ini1 - 1;
        }
    }
    return inv;
}

int main(){
    int n;
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++){
        cin >> vec[i];
    }
    cout << count(vec);
}