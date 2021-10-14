#include <bits/stdc++.h>
#include "libgen/lib/tree.hpp"
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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));
std::mt19937_64 rng64(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

template<typename T> T rnd(T v) {
  T k;
  if constexpr(sizeof(T) <= 32) k = (T) rng(); else k = (T) rng64();
  return (T) (((k % v) + v) % v);
}

template<typename T> T rnd(T l, T r) {
  if (r < l) swap(l, r);
  return (T) (l + rnd(r - l + 1));
}

int main() {
	// int n = 5, m = 20, q = 3;
	// int n = 5, m = 20, q = 3;
	int n = 100000, m = 150000, q = 150000;
	// int n = 2000, m = 2000, q = 1000;
	// int n = 4, m = 2, q = 2;
	cout << n << ' ' << m << ' ' << q << '\n';
	libgen::Tree t;
	t.generate_blocks(n, 100, rng);
	for(auto it : t)
		cout << it.first << ' ' << it.second << ' ' << rnd(1, m) << '\n';
	// for(int i = 1; i < n; i++)
	// 	cout << i << ' ' << i+1 << ' ' << rnd(1, m) << '\n';
	while(q--) {
		if(rnd(2)) cout << "Z " << rnd(1, n) << '\n';
		else cout << "B " << rnd(1, n-1) << ' ' << rnd(1, m) << '\n';
	}
}
