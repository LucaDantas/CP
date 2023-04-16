
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;

int a[maxn];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    sort(a+1, a+1+n, greater<int>());
    int ganha = -1;
    for(int i = 1; i <= n; i++)
        if(i > m/a[i])
            ganha = a[i];
    if(ganha == -1) {
        puts("Alessia"); fflush(stdout);
        vector<int> colocados = {0, m+1};
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j+1 < (int)(colocados.size()); j++)
                if(colocados[j+1] - colocados[j] > a[i])
                    { printf("%d %d\n", a[i], colocados[j]+1); fflush(stdout); break; }
            int x; scanf("%d", &x);
            colocados.push_back(x); sort(colocados.begin(), colocados.end()); // nao precisa ser eficiente entao fds
        }
    } else {
        puts("Bernardo"); fflush(stdout);
        while(n--) {
            int sz, x; scanf("%d %d", &sz, &x);
            int ans = x + ganha - (x % ganha); // chega no proximo multiplo do que precisa pra ganhar
            if(ans >= x + sz)
                ans = x;
            printf("%d\n", ans); fflush(stdout);
        }
    }
}
