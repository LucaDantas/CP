#include<bits/stdc++.h>
using namespace std;

#define MAXN 100100
#define pii pair<int, int>

int p[MAXN], f[MAXN];
pii a[MAXN];

bool ord(pii a, pii b){
    if(a.second > b.second) return a > b;
    if(b.second > a.second) return b > a;
    if(a.first > b.second) return a > b;
    return b > a;
}

int main(){
    int n, gforce = 0, g = 0, l = MAXN, lforce = MAXN;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> p[i] >> f[i];
        if(g < p[i]+f[i]){
            gforce = f[i];
        }
        a[i] = make_pair(i, p[i]+f[i]);
    }
    sort(a+1, a+1+n, ord);
    int res = gforce;
    cout << gforce << endl;
    bool broke = false;
    for(int i = 2; i <= n-1; i++){
        cout << "HI" << endl;
        res = min(res, f[i]) - p[i];
        if(res < 0){
            cout << "IMPOSSIVEL" << endl;
            broke = true;
            break;
        } 
    }
    if(!broke && res - p[n] < 0){
        cout << res - p[n] << endl;
        cout << "IMPOSSIVEL" << endl;
        broke = true;
    }
    if(!broke){
        for(int i = 1; i <= n; i++){
            cout << a[i].first << endl;
        }
    }
}