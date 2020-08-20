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
constexpr int maxn = 1e6 + 10;
constexpr int mod = 1000000007;
constexpr int S = 200;

struct Qr
{
	int l, r, i;
};

int cnt[maxn];
vector<Qr> Q;
vi resp;

int main() {
	int n; scanf("%d", &n);
	vi a(n+1); rep(i,1,n+1) scanf("%d", &a[i]);
	int q; scanf("%d", &q);
	resp.resize(q);
	rep(i,0,q) {
		int x, y; scanf("%d %d", &x, &y);
		Q.pb({x, y, i});
	}
	sort(all(Q), [&](const Qr& x, const Qr& y){
		return make_pair(x.l/S, x.r) < make_pair(y.l/S, y.r);
	});
	int l = Q[0].l, r = Q[0].r, ans = 0;
	rep(i,l,r+1) {cnt[a[i]]++; if(cnt[a[i]] == 1) ans++;}
	for(auto qr : Q) {
		while(l > qr.l) {
			cnt[a[--l]]++;
			if(cnt[a[l]] == 1) ans++;
		}
		while(l < qr.l) {
			cnt[a[l++]]--;
			if(cnt[a[l-1]] == 0) ans--;
		}
		while(r > qr.r) {
			cnt[a[r--]]--;
			if(cnt[a[r+1]] == 0) ans--;
		}
		while(r < qr.r) {
			cnt[a[++r]]++;
			if(cnt[a[r]] == 1) ans++;
		}
		resp[qr.i] = ans;
	}
	rep(i,0,q) printf("%d\n", resp[i]);
}
