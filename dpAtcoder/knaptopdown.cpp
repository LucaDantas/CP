#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define MAXN 110
#define MAXS 100100

vector<pii> vec;
long long tab[MAXS][MAXN];
int n;

long long dp(int w, int ind){
    if(w == 0 || ind == n) return 0;
    if(tab[w][ind] >= 0) return tab[w][ind];
    long long coloca = (w - vec[ind].first >= 0)? vec[ind].second + dp(w-vec[ind].first, ind+1) : 0;
    long long nao_coloca = dp(w, ind+1);
    tab[w][ind] = max(coloca, nao_coloca);
    return max(coloca, nao_coloca);
}

int main(){
    int r;
    scanf("%d%d", &n, &r);
    vec.resize(n);
    memset(tab,-1,sizeof tab);
    for(int i = 0, p, v; i < n; i++){
        scanf("%d%d", &p ,&v);
        vec[i] = make_pair(p, v);
    }
    printf("%lld\n", dp(r, 0));
}