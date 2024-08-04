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
constexpr int maxn = 1e4 + 10;
constexpr int mod = 1000000007;

vector<int> g[maxn], grp[2];
int cor[maxn];

bool dfs(int u) {
    grp[cor[u]].push_back(u);
    bool ok = 1;
    for(int v : g[u]) {
        if(cor[v] == -1)
            cor[v] = cor[u]^1, ok &= dfs(v);
        else if(cor[v] == cor[u])
            ok = 0;
    }
    return ok;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);
        for(int i = 0, a, b; i < m; i++)
            scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
        for(int i = 1; i <= n; i++)
            cor[i] = -1;
        cor[1] = 0;
        bool bip = dfs(1);

        if(bip) {
            // play as bob
            puts("Bob");
            fflush(stdout);
            for(int i = 1; i <= n; i++) {
                int c[2]{};
                for(int k : {0, 1})
                    scanf("%d", c+k);
                bool tem1 = c[0] == 1 || c[1] == 1, tem2 = c[0] == 2 || c[1] == 2;
                if(grp[0].empty()) {
                    printf("%d %d\n", grp[1].back(), tem2 ? 2 : 3);
                    grp[1].pop_back();
                } else if(grp[1].empty()) {
                    printf("%d %d\n", grp[0].back(), tem1 ? 1 : 3);
                    grp[0].pop_back();
                } else {
                    if(tem1)
                        printf("%d %d\n", grp[0].back(), 1), grp[0].pop_back();
                    else
                        printf("%d %d\n", grp[1].back(), 2), grp[1].pop_back();
                }
                fflush(stdout);
            }
        } else {
            // play as alice, just always send colors 1 and 2
            puts("Alice");
            fflush(stdout);
            for(int i = 1; i <= n; i++) {
                puts("1 2");
                fflush(stdout);
                int lixo1, lixo2; scanf("%d %d", &lixo1, &lixo2);
            }
        }
        // TODO: clean things up, cor is cleaned in the beginning
        for(int i = 1; i <= n; i++)
            g[i].clear();
        grp[0].clear(), grp[1].clear();
    }
}
