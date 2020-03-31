#include<bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define MAXN 1010
#define INF 1e9 + 100

int n, ans = -1;
vector<pii> v;
int save[MAXN][MAXN];

//dp(item to use or not, nb of items) = minimum weight
int dp(int l, int nb){
    if(l >= n) return 0;
    if(save[l][nb] != INF) return save[l][nb];
    int coloca = dp(l+1, nb+1)+v[l].second;
    int nao_coloca = dp(l+1, nb);
    ans = max(ans, nb);
    if(v[l].first >= coloca){
        save[l][nb] = min(save[l][nb], min(coloca, nao_coloca));    }
    else{
        save[l][nb] = min(save[l][nb], nao_coloca);
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1, p, r; i <= n; i++){
        scanf("%d%d", &p, &r);
        v.push_back(make_pair(-r, p));
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            save[i][j] = INF;
        }
    }
    dp(0,0);
    printf("%d\n", ans);
}