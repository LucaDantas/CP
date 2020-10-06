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

int tam[maxn], last[maxn][2];

int main() {
	fast;
	string s; cin >> s;
	int n = sz(s);
	reverse(all(s));
	vector<string> ans;
	string here = "";
	bool remove = 0;
	clr(last, -1);
	for(int i = 0; i < n; i++) {
		int cima = -1, baixo = -1;
		for(int j = 0; j < 26; j++) {
			if(j < s[i]-'a')
				baixo = max(baixo, last[j][0]);
			if(j > s[i]-'a')
				cima = max(cima, last[j][0]);
		}
		
		if(remove && last[s[i]-'a'][0] == i-1 && baixo >= cima) {
			remove = 0;
			here.pop_back();
			last[s[i]-'a'][0] = last[s[i]-'a'][1];
		} else {
			remove = 1;
			last[s[i]-'a'][1] = last[s[i]-'a'][0];
			last[s[i]-'a'][0] = i;
			here.pb(s[i]);
		}

		if(sz(here) <= 10) {
			reverse(all(here));
			ans.pb(here);
			tam[n-1-i] = sz(here);
			reverse(all(here));
		} else {
			string massa = "";
			for(int p = sz(here)-1; p >= sz(here)-5; p--)
				massa.pb(here[p]);
			massa += "...";
			for(int p = 1; p >= 0; p--)
				massa.pb(here[p]);
			ans.pb(massa);
			tam[n-1-i] = sz(here);
		}
	}
	reverse(all(ans));
	for(int i = 0; i < n; i++)
		cout << tam[i] << ' ' << ans[i] << '\n';
}
