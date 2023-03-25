// Educational 145 E
#include <bits/stdc++.h>
using namespace std;

constexpr int maxv = 2010, maxn = 1e4+10;

int dp[maxv][2], a[maxn];

pair<int,int> mx = {-maxv, 0}, mn = {maxv, 0};

int pref = 0;

int main() {
    int n, L, R; scanf("%d %d %d", &n, &L, &R);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i), pref += a[i], mx = max(mx, {pref, i}), mn = min(mn, {pref, i});
    for(int soma = 0; soma <= L+R; soma++) {
        {
            // valor todo na esquerda
            int l = min(soma, L), r = soma - l;
            for(int i = mn.second + 1; i <= n; i++) {
                if(a[i] > 0) {
                    int val = min({a[i], l, R-r});
                    l -= val;
                    r += val;
                } else {
                    int val = min({-a[i], r, L-l});
                    r -= val;
                    l += val;
                }
            }
            dp[soma][0] = l;
        }
        {
            // valor todo na direita
            int r = min(soma, R), l = soma - r;
            for(int i = mx.second + 1; i <= n; i++) {
                if(a[i] > 0) {
                    int val = min({a[i], l, R-r});
                    l -= val;
                    r += val;
                } else {
                    int val = min({-a[i], r, L-l});
                    r -= val;
                    l += val;
                }
            }
            dp[soma][1] = l;
        }
    }
    for(int l = 0; l <= L; l++) {
        for(int r = 0; r <= R; r++) {
            if(mx.first >= l || mx.first + r >= R)
                printf("%d ", dp[l+r][1]); // estourou com o valor todo na direita
            else if(-mn.first >= r || -mn.first + l >= L)
                printf("%d ", dp[l+r][0]); // estourou na esquerda
            else
                printf("%d ", l - pref); // nao estourou em canto nenhum entao eu so conto normal
        }
        puts("");
    }
}
