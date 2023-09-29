#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;

int n, m;
char s[maxn];
bool a[maxn][maxn];

vector<pair<int,int>> marks;
vector<int> caminho[maxn*maxn];

int id[maxn<<1][maxn<<1], ans[maxn*maxn];

void pre() {
    int x = maxn, y = maxn, pos = 0;
    id[x][y] = pos++;
    for(int camada = 1; min(x, y) > 0 && max(x, y)+1 < (maxn<<1); camada += 2) {
        --x;
        id[x][y] = pos++;
        for(int i = 0; i < camada && min(x, y) > 0 && max(x, y)+1 < (maxn<<1); i++)
            ++y, id[x][y] = pos++;
        for(int i = 0; i < camada+1 && min(x, y) > 0 && max(x, y)+1 < (maxn<<1); i++)
            ++x, id[x][y] = pos++;
        for(int i = 0; i < camada+1 && min(x, y) > 0 && max(x, y)+1 < (maxn<<1); i++)
            --y, id[x][y] = pos++;
        for(int i = 0; i < camada+1 && min(x, y) > 0 && max(x, y)+1 < (maxn<<1); i++)
            --x, id[x][y] = pos++;
    }
}

vector<pair<vector<int>, int>> opa;

int main() {
    memset(id, -1, sizeof id);
    pre();
    scanf("%d %d", &m, &n); // de proposito invertido n e m, assim que o enunciado da
    for(int i = 0; i < n; i++) {
        scanf(" %s", s);
        for(int j = 0; j < m; j++) {
            a[i][j] = s[j] == 'X';
            if(a[i][j])
                marks.push_back({i, j});
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(auto [x, y] : marks)
                caminho[i*m+j].push_back(id[maxn + x-i][maxn + y-j]);
            sort(caminho[i*m+j].begin(), caminho[i*m+j].end());
            opa.push_back({caminho[i*m+j], i*m+j});
        }
    }

    sort(opa.begin(), opa.end());

    // for(auto [a, b] : opa) {
    //     printf("(%d %d) = ", b/m, b%m);
    //     for(int x : a)
    //         printf("%d ", x);
    //     puts("");
    // }

    auto dif = [](vector<int>& x, vector<int>& y) -> int {
        int sz = (int)(x.size());
        
        for(int i = 0; i < sz; i++)
            if(x[i] != y[i])
                return min(x[i], y[i]);

        assert(0);
        return -1;
    };

    for(int i = 0; i < (int)(opa.size()); i++) {
        if(i) ans[opa[i].second] = dif(opa[i-1].first, opa[i].first);
        if(i+1 < (int)(opa.size())) ans[opa[i].second] = max(ans[opa[i].second], dif(opa[i].first, opa[i+1].first));
    }

    int soma = 0, mx = 0;

    for(int val = 0; val < (int)(opa.size()); val++) {
        soma += ans[val];
        mx = max(mx, ans[val]);
    }

    printf("%.10lf\n", (double)(soma) / (double)opa.size());
    printf("%d\n", mx);
    vector<pair<int,int>> resp;
    for(int val = 0; val < (int)(opa.size()); val++) if(ans[val] == mx) {
        int i = val/m, j = val%m;
        resp.push_back({j+1, n-i});
    }
    sort(resp.begin(), resp.end(), [](pair<int,int> x, pair<int,int> y){
        if(x.second == y.second) return x.first < y.first;
        return x.second < y.second;
    });
    for(auto [x, y] : resp)
        printf("(%d,%d) ", x, y);
    puts("");
}
