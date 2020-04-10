#include<bits/stdc++.h>
using namespace std;

vector<int> vec;

int count(vector<int> &v){
    int n = (int)v.size();
    if(n <= 1) return 0;
    vector<int> u1, u2;
    for(int i = 0; i < n/2; i++){
        u1.push_back(v[i]);
    }
    for(int i = n/2; i < n; i++){
        u2.push_back(v[i]);
    }
    int inv = count(u1) + count(u2);
    u1.push_back(-1);
    u2.push_back(-1);
    int pos1 = 0, pos2 = 0;
    for(int i = 0; i < n; i++){
        if(u2[pos2] >= u1[pos1]){
            v[i] = u2[pos2++];
            inv += u1.size() - pos1 - 1;
        }
        else v[i] = u1[pos1++];
    }
    return inv;
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
	cin >> n;
    vec.resize(n);
    for(int i = 0, x, y; i < n; i++){
        cin >> x >> y;
        vec[i] = sqrt(x*x + y*y);
    }
    cout << count(vec) << '\n';
}
