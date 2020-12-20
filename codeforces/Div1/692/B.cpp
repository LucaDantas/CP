#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }


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

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int pref[maxn][3], suf[maxn][3];

int main() {
	fast;
	string s; cin >> s;
	ll x, y; cin >> x >> y;
	for(int i = 0; i < sz(s); i++) {
		if(i) {
			pref[i][0] = pref[i-1][0];
			pref[i][1] = pref[i-1][1];
			pref[i][2] = pref[i-1][2];
		}
		++pref[i][s[i]=='?'?2:(s[i]=='1')];
	}
	for(int i = sz(s)-1; i >= 0; i--) {
		suf[i][0] = suf[i+1][0];
		suf[i][1] = suf[i+1][1];
		suf[i][2] = suf[i+1][2];
		++suf[i][s[i]=='?'?2:(s[i]=='1')];
	}
	ll here = 0, ans;
	for(int i = 0; i < sz(s); i++) {
		if(s[i] == '?' || s[i] == '0')
			here += y*pref[i][1];
		else here += x*(pref[i][0] + pref[i][2]);
	}
	ans = here;
	for(int i = 0; i < sz(s); i++) {
		if(s[i] == '?') {
			here -= x*suf[i][1] + y*(pref[i][1]+pref[i?i-1:sz(s)+5][2]);
			here += x*pref[i][0] + y*(suf[i][0]+suf[i+1][2]);
			ans = min(ans, here);
		}
	}

	here = 0;
	for(int i = 0; i < sz(s); i++) {
		if(s[i] == '?' || s[i] == '1')
			here += x*pref[i][0];
		else here += y*(pref[i][1] + pref[i][2]);
	}
	ans = min(ans, here);
	for(int i = 0; i < sz(s); i++) {
		if(s[i] == '?') {
			here -= y*suf[i][0] + x*(pref[i][0]+pref[i?i-1:sz(s)+5][2]);
			here += y*pref[i][1] + x*(suf[i][1]+suf[i+1][2]);
			ans = min(ans, here);
		}
	}

	cout << ans << '\n';
}
