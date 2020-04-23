#include<bits/stdc++.h>
using namespace std;

#define INF 1e9 + 100

vector<int> vec;

int merge(vector<int> &v){
    if((int)v.size() == 1) return 0;
    vector<int> u1, u2;
    for(int i = 0; i < (int)v.size()/2; i++){
        u1.push_back(v[i]);
    }
    for(int i = (int)v.size()/2; i < (int)v.size(); i++){
        u2.push_back(v[i]);
    }
    int inv = merge(u1) + merge(u2);
    u1.push_back(INF);
    u2.push_back(INF);
    int pos1 = 0, pos2 = 0;
    for(int i = 0; i < (int)v.size(); i++){
        if(u2[pos2] < u1[pos1]){
            inv += (int)u1.size() - pos1 - 1;
            v[i] = u2[pos2++];
        }
        else 
            v[i] = u1[pos1++];
    }
    return inv;
}

int main(){
    int n;
    scanf("%d", &n);
    vec.resize(n);
    for(int i = 0, a; i < n; i++){
        scanf("%d", &vec[i]);
    }
    printf("%d\nff", merge(vec));
}