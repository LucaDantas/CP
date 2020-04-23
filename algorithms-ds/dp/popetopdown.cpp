#include<bits/stdc++.h>
using namespace std;

#define MAXN 1010
#define INF 1000000100
int n, tab[MAXN][MAXN];

vector<pair<int, int> > vec;

int dp(int ind, int k){
    if(n - ind < k) return INF;
    if(k == 0) return 0;
    if(tab[ind][k] != -1){
        return tab[ind][k];
    } 
    int coloca = vec[ind].second + dp(ind+1, k-1);
    int nao_coloca = dp(ind+1, k);
    bool a = vec[ind].first >= coloca;
    if(a){
        tab[ind][k] = min(coloca, nao_coloca);
        return min(coloca, nao_coloca);
    }
    tab[ind][k] = nao_coloca;
    return nao_coloca;
}

int main(){
    scanf("%d", &n);
    vec.resize(n);
    for(int i = 0, p, r; i < n ; i++){
        scanf("%d%d", &p, &r);
        vec[i] = make_pair(r, p);
    }
    memset(tab, -1, sizeof tab);
    sort(vec.begin(), vec.end(), greater<pair<int,int> >());
    int i = n;
    while(i > 0){
        if(dp(0,i) < INF){
            printf("%d\n", i);
            break;
        }
        i--;
    }
    if(i == 0) printf("%d", -1);
}