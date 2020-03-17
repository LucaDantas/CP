#include<bits/stdc++.h>
using namespace std;

vector<int> vec;

int count(vector<int> &v){
    int inv = 0;
    if(v.size() == 1) return 0;
    vector<int> u1, u2;
    for(int i = 0, i < v.size()/2; i++){
        u1.push_back(v[i]);
    }
    for(int i = v.size()/2; i < v.size(); i++){
        u2.push_back(v[i]);
    }
    inv += count(u1) + count(u2);
    
}

int main(){
    

}