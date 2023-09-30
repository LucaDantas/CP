#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

double p[maxn][maxn];

void pre() {
    for(int sz = 1; sz < maxn; sz++) {
        for(int i = 1; i <= sz; i++) {
            if(i == 1)
                p[sz][i] = 1.0/sz;
            else {
                p[sz][i] = (double)(i-2)/sz * p[sz-2][i-2] // escolho um cara menor que eu
                    + (double)(sz-i)/sz * p[sz-2][i-1]; // escolho um cara maior que eu
            }
        }
    }
}

int main() {
    pre();
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);
        vector<vector<int>> g(n+1);
        for(int i = 0, a, b; i < m; i++)
            scanf("%d %d", &a, &b), g[a].push_back(b);
        vector<double> dp(n+1);
        dp[n] = 1;
        for(int i = n-1; i >= 1; i--) {
            vector<double> lista;
            for(int x : g[i])
                lista.push_back(dp[x]);
            sort(lista.begin(), lista.end(), greater<double>());
            for(int j = 0; j < (int)(lista.size()); j++)
                dp[i] += lista[j] * p[lista.size()][j+1];
        }
        printf("%.10lf\n", dp[1]);
    }
}
