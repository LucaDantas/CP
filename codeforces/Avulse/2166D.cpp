#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010, mod = 998244353;

int dp[2][maxn];

// tenho que calcular quantos ativos vao ter no total
// bruto esse valor
// pra cada um eu posso escolher como distribuir os valores
// pra cada cara eu tenho um maximo que eu posso colocar como ativo (e um minimo tbm)
// depois meto paus e bolas

inline void add_self(int& x, int y) { x = (x + y) % mod; }

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> cnt(n+1);
        int maior = 0;
        for(int i = 0, x = 0; i < n; i++) {
            scanf("%d", &x), cnt[x]++;
            if(cnt[x] > cnt[maior])
                maior = x;
        }

        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) if(i != maior) {
            for(int soma = 0; soma <= n; soma++) {
                add_self(dp[1][soma], dp[0][soma]);
                if(soma + cnt[i] <= n)
                    add_self(dp[1][soma + cnt[i]], (int)(1ll * dp[0][soma] * cnt[i] % mod));
            }
            for(int soma = 0; soma <= n; soma++)
                dp[0][soma] = dp[1][soma], dp[1][soma] = 0;
        }


        int ans = 0;
        for(int soma = cnt[maior]; soma <= n; soma++)
            add_self(ans, dp[0][soma]);
        for(int soma = 0; soma <= n; soma++)
            add_self(ans, 1ll * dp[0][soma] * cnt[maior] % mod);
        printf("%d\n", ans);
    }
}
