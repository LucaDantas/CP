#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define MAXN 2010

vector<pii> vec;
int tab[MAXN][MAXN], n;

int dp(int w, int ind){
    if(w == 0 || ind == n) return 0;
    if(tab[w][ind] >= 0) return tab[w][ind];
    int coloca = (w - vec[ind].first >= 0)? vec[ind].second + dp(w-vec[ind].first, ind+1) : 0;
    int nao_coloca = dp(w, ind+1);
    tab[w][ind] = max(coloca, nao_coloca);
    return max(coloca, nao_coloca);
}

int main(){
    int r;
    scanf("%d%d", &r, &n);
    vec.resize(n);
    // for(int i = 0; i < MAXN; i++){
    //     for(int j = 0; j < MAXN; j++){
    //         tab[i][j] = -1;
    //     }
    // }
    memset(tab,-1,sizeof tab);
    for(int i = 0, p, v; i < n; i++){
        scanf("%d%d", &p ,&v);
        vec[i] = make_pair(p, v);
    }
    printf("%d\n", dp(r, 0));
}