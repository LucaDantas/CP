#include<bits/stdc++.h>
using namespace std;

#define MAXN 110

int v[MAXN];

int main(){
    int n, c, s, p, now = 1;
    cin >> n >> c >> s;
    v[1] = 1;
    for(int i = 0; i < c; i++){
        cin >> p;
        now+=p;
        if(now < 1) now = n;
        else if(now > n) now = 1;
        v[now]++;
    }
    cout << v[s] << endl;
}