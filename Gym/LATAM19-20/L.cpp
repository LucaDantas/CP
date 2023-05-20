#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int maxn = 1010;

char s[maxn];

int a[maxn][maxn], dp[maxn][maxn];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    rep(i,0,n) {
        scanf(" %s", s);
        rep(j,0,m)
            a[i][j] = s[j] == 'G';
    }
    rep(i,0,n) dp[0][i] = dp[i][0] = 1;
    rep(i,1,n) rep(j,1,m)
        dp[i][j] = (a[i][j] == a[i][j-1] && a[i-1][j] == a[i-1][j-1] ? min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) : 0) + 1;
    int ans = 1;
    rep(i,0,n) rep(j,0,m)
        ans = max(ans, dp[i][j]);
    printf("%d\n", ans*ans);
}
