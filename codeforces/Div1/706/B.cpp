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
	int n; scanf("%d", &n);
	vector<int> p = {inf};
	for(int i = 1, x; i <= n; i++)
		scanf("%d", &x), p.pb(x);
	p.pb(inf);
	vector<int> peaks, valleys;
	for(int i = 1; i <= n; i++) {
		if(p[i] > p[i-1] && p[i] > p[i+1]) peaks.pb(i);
		if(p[i] < p[i-1] && p[i] < p[i+1]) valleys.pb(i);
	}
	int ans = 0, maior = max(valleys[0]-1, n - valleys.back()), cnt_maior = 1;
	for(int i = 0; i < sz(peaks); i++) {
		auto it = upper_bound(all(valleys), peaks[i]);
		if(it == valleys.end() || it == valleys.begin()) assert(0);
		int s1 = peaks[i] - *prev(it), s2 = *it - peaks[i];
		if(max(s1, s2) > maior) cnt_maior = 1, maior = max(s1, s2);
		else if(max(s1, s2) == maior) ++cnt_maior;
		// printf("%d %d %d\n", peaks[i], s1, s2);
	}

	for(int i = 0; i < sz(peaks); i++) {
		auto it = upper_bound(all(valleys), peaks[i]);
		if(it == valleys.end() || it == valleys.begin()) assert(0);
		int s1 = peaks[i] - *prev(it), s2 = *it - peaks[i];
		if(s1 == s2 && !(s1%2) && s1 == maior && cnt_maior == 1) ++ans;
		// printf("%d %d %d\n", peaks[i], s1, s2);
	}
	printf("%d\n", ans);
}
