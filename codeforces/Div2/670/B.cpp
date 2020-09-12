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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int main() {
    fast;
	int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> a(n); for(int i = 0; i < n; i++) cin >> a[i];
        sort(all(a));
        bool ok = 0;
        int cnt = 0, oto = 0;
        vector<ll> pos, neg;
        for(int i = 0; i < n; i++) {
            if(a[i] == 0) ok = 1;
            cnt += a[i] < 0;
            oto += a[i] > 0;
            if(a[i] > 0) pos.pb(a[i]);
            if(a[i] < 0) neg.pb(a[i]);
        }
        
        ll ans = 1;
        if(!oto) { // se eu não tenho ninguem positivo quero pegar os menores em valor abs (maiores)
            if(ok) {
                cout << "0\n";
                continue;
            }
            int opa = 5;
            sort(all(neg)); // os maiores vem por ultimo
            while(opa--) {
                ans *= neg.back();
                neg.pop_back();
            }
            cout << ans << '\n';
            continue;
        } else {
            if((oto-1) - (oto-1)%2 + (cnt) - (cnt)%2 < 4) {
                if(ok) {
                    cout << "0\n";
                    continue;
                } else {
                    // assert(n == 5);
                    for(auto x : a)
                        ans *= x;
                    cout << ans << '\n';
                    continue;
                }
            }
            else {
                // nesse caso a gente tem certeza que o resultado pode ser positivo
                // já que oto >= 1 e (oto-1) - (oto-1)%2 + (cnt) - (cnt)%2 >= 4
                // if((oto-1) - (oto-1)%2 + (cnt) - (cnt)%2 < 4) {cout << "EOQ"; continue;}
                assert((oto-1) - (oto-1)%2 + (cnt) - (cnt)%2 >= 4);
                sort(all(pos)); sort(all(neg), greater<int>());
                ans = pos.back(); // maior vai sempre entrar já q é positivo
                pos.pop_back();
                for(int massa = 0; massa < 2; massa++) {
                    if(sz(pos) < 2) {
                        // assert(sz(neg) >= 2);
                        ans *= neg.back();
                        neg.pop_back();
                        ans *= neg.back();
                        neg.pop_back();
                    }
                    else if(sz(neg) < 2) {
                        // assert(sz(pos) >= 2);
                        ans *= pos.back();
                        pos.pop_back();
                        ans *= pos.back();
                        pos.pop_back();
                    }
                    else {
                        // assert(sz(neg) >= 2);
                        // assert(sz(pos) >= 2);
                        if(pos.back() * pos[sz(pos)-2] > neg.back() * neg[sz(neg)-2]) {
                            ans *= pos.back();
                            pos.pop_back();
                            ans *= pos.back();
                            pos.pop_back();
                        } else {
                            ans *= neg.back();
                            neg.pop_back();
                            ans *= neg.back();
                            neg.pop_back();
                        }
                    }
                }
                cout << ans << '\n';
                continue;
            }
        }
        
    }
}
