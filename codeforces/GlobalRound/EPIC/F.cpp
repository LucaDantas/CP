#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 805;
constexpr int mod = 1000000007;

int a[maxn];
int dp[maxn][maxn];

int ans[maxn]; // maior quantidade que consigo matar terminando aqui

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        memset(dp, 0x3f, sizeof dp);

        int n; scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%d", a+i);

        for(int sz = 2; sz <= n; sz += 2) {
            for(int l = 1; l + sz - 1 <= n; l++) {
                if(a[l] > l || (l-a[l]) % 2) continue; // impossivel ent fds

                int r = l + sz - 1;
                if(sz == 2)
                    dp[l][r] = (l-a[l])>>1; // a gente ja sabe que a[l] <= l e eh da mesma paridade
                else {
                    int matar_filhos = (l-a[l]) >> 1;

                    // mato l com r
                    for(int meio = l+2; meio <= r-1; meio += 2) {
                        if(dp[l+1][meio] <= matar_filhos &&
                                (meio+1==r || dp[meio+1][r-1] <= matar_filhos + (meio - l) / 2)) {
                            dp[l][r] = matar_filhos;
                            break;
                        }
                    }

                    // mato l com meio e pego o resto separado
                    for(int meio = l+1; meio < r; meio += 2)
                        if(dp[l][meio] <= matar_filhos && dp[meio+1][r] <= matar_filhos + (meio-l+1)/2)
                            dp[l][r] = matar_filhos;
                }

            }
        }

        for(int r = 1; r <= n; r++) {
            ans[r] = ans[r-1];
            for(int l = 1; l < r; l++)
                if(dp[l][r] <= ans[l-1])
                    ans[r] = max(ans[r], ans[l-1] + (r-l+1)/2);
        }

        printf("%d\n", ans[n]);
    }
}
