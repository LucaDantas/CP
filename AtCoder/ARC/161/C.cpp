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
#define sz(a) ((int)(a).size())
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

int fim[maxn], val[maxn], grau[maxn], cor[maxn];
bool mark[maxn];
vector<int> g[maxn];

void clear(int n) {
    for(int i = 1; i <= n; i++)
        g[i].clear(), fim[i] = val[i] = grau[i] = cor[i] = mark[i] = 0;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        clear(n);
        for(int i = 1, a, b; i < n; i++)
            scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a), ++grau[a], ++grau[b];
        for(int i = 1; i <= n; i++) {
            char c; scanf(" %c", &c);
            fim[i] = c == 'W' ? 1 : -1;
        }
        queue<int> q;
        for(int i = 1; i <= n; i++)
            if(grau[i] == 1) q.push(i);
        bool ok = 1;
        while(q.size()) {
            int u = q.front(), pai = -1; q.pop();
            mark[u] = 1;

            for(int v : g[u]) if(!mark[v])
                pai = v;

            if(pai == -1) {
                ok &= fim[u] * val[u] > 0;
                break; // cheguei na raiz entao acabou
            }

            if(--grau[pai] == 1)
                q.push(pai);

            if(val[u]) 
                ok &= fim[u] * val[u] > 0; // a cor do cara ja ta definida, nao tem mais oq pedir pro pai
            else
                ok &= (cor[pai] == 0 || cor[pai] == fim[u]), cor[pai] = fim[u];

            if(!cor[u])
                cor[u] = fim[pai];
            val[pai] += cor[u];
        }
        if(ok) {
            for(int i = 1; i <= n; i++)
                putchar(cor[i] == 1 ? 'W' : 'B');
            putchar('\n');
        } else
            puts("-1");
    }
}
