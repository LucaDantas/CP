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
constexpr int maxn = 1e5+2000;
constexpr int mod = 1000000007;

// 9592 primes <= 1e5, sqrt(1e5) == 317, 65 primes < 317

bool f[maxn], mark[maxn];
vi pr;

void sieve() {
    for(int i = 2; i*i < maxn; i++) {
        if(!f[i])
            for(int j = i+i; j < maxn; j += i)
                f[j] = 1;
    }
    for(int i = 2; i < maxn; i++)
        if(!f[i])
            pr.pb(i);
}

int32_t main() {
	sieve();
    fast;
    int n, rmv = 0; cin >> n;
    // 65 queries
    for(int i = 0; pr[i] < min(n+1, 317); i++) {
        cout << "B " << pr[i] << endl;
        int x; cin >> x;
    }
    for(int i = 0; pr[i] < min(n+1, 317); i++)
        for(int j = pr[i]; j <= n; j += pr[i])
            mark[j] = 1;
    for(int i = 2; i <= n; i++)
        rmv += mark[i];
    // 66 queries
    cout << "A 1" << endl;
    int tem; cin >> tem;
    int gigante = 1; // fator primo >= 317

    bool sem_peq = tem == n - rmv;

    // 9593 queries
    for(int i = 65; pr[i] <= n; i += 100) {
        int remover = 0; // quantos eu tenho que remover / quantos eu removi mesmo
        for(int j = i; pr[j] <= n && j < i + 100; j++) {
            cout << "B " << pr[j] << endl;
            int x; cin >> x;
            remover += x;
        }
        
        cout << "A 1" << endl;
        int opa; cin >> opa;

        if(opa + remover > tem) {
            // o cara tá nesse grupo
            for(int j = i; pr[j] <= n && j < i + 100; j++) {
                cout << "A " << pr[j] << endl;
                int x; cin >> x;
                if(x == 1) gigante = pr[j];
            }
            break;
        }

        tem = opa;
    }

    if(sem_peq) {
        cout << "C " << gigante << endl;
        return 0;
    }

    cout << "A 1" << endl;
    int massa; cin >> massa;
    if(massa == 1) {
        cout << "C 1" << endl;
        return 0;
    }

    // 9800 queries +=, então a gente tem 200 pra achar os fatores pequenos

    // se não tiver fator gigante n faz mal, vai ser 1
    int ans = gigante;

    for(int i = 0; i < 65 && 1ll * ans * pr[i] <= n; i++) {
        while(1ll * ans * pr[i] <= 1ll * n) {
            cout << "A " << ans * pr[i] << endl;
            int x; cin >> x;
            if(x) ans *= pr[i];
            else break;
        }
    }

    cout << "C " << ans << endl;
}
