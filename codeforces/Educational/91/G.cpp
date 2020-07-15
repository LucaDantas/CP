#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

namespace utils{
	constexpr bool use_stdio = false;
	ostream* out = &cout;
	FILE* stdio_out = stdout;
	const bool __ = [](){ if constexpr(!use_stdio){ ios_base::sync_with_stdio(false); cin.tie(nullptr);
	  cout << fixed; cout << setprecision(12); cerr << fixed; cerr << setprecision(12); } return true; }();
	template<typename ...> using to_void = void;
	template<typename T, typename = void> struct is_container : false_type {};
	template<typename T> struct is_container<T, to_void<decltype(declval<T>().begin()), decltype(declval<T>().end())>> : true_type {};

	inline void rd(int& x) { if constexpr(use_stdio) scanf("%d", &x); else cin >> x; }
	inline void rd(long long& x) { if constexpr(use_stdio) scanf("%lld", &x); else cin >> x; }
	inline void rd(double& x) { if constexpr(use_stdio) scanf("%lf", &x); else cin >> x; }
	inline void rd(long double& x) { if constexpr(use_stdio){ double y; scanf("%lf", &y); x=y; } else cin >> x; }
	inline void rd(char& x) { if constexpr(use_stdio) scanf(" %c", &x); else cin >> x; }
	inline void rd(char* x) { if constexpr(use_stdio) scanf("%s", x); else cin >> x; }
	inline void rd(string& x) { if constexpr(use_stdio) assert(false); else cin >> x; }
	template<typename T, typename enable_if<!use_stdio && is_integral<T>::value>::type* = nullptr> inline void rd(T& x) { cin >> x; }
	template<typename T> inline void rd(T* x);
	template<typename T, typename enable_if<is_container<T>::value>::type* = nullptr> inline void rd(T& x);
	template<typename... Ts> inline void rd(tuple<Ts...>& x);
	template<typename T, typename U> inline void rd(pair<T, U>& x) { rd(x.first); rd(x.second); }
	template<typename T, typename enable_if<is_container<T>::value>::type* = nullptr> inline void rd(T& x) { for(auto& v : x) rd(v); }
	template<typename T, typename U, typename... Ts> inline void rd(T&& t, U&& u, Ts&&... ts) {
	  rd(forward<T>(t)); rd(forward<U>(u), forward<Ts>(ts)...); }
	template<typename... Ts> inline void rd(tuple<Ts...>& x) { static_assert(sizeof...(Ts) > 0);
	  constexpr auto apply_rd = [](auto&&... xs) { rd(xs...); }; apply(apply_rd, x); }
	template<typename T> inline void rd(T* x) { rd(*x); }

	inline void prt(const int& x) { if constexpr(use_stdio) fprintf(stdio_out, "%d", x); else *out << x; }
	inline void prt(const long long& x) { if constexpr(use_stdio) fprintf(stdio_out, "%lld", x); else *out << x; }
	inline void prt(const double& x) { if constexpr(use_stdio) fprintf(stdio_out, "%.12f", x); else *out << x; }
	inline void prt(const long double& x) { if constexpr(use_stdio) fprintf(stdio_out, "%.12f", (double)x); else *out << x; }
	inline void prt(const char& x) { if constexpr(use_stdio) fprintf(stdio_out, "%c", x); else *out << x; }
	inline void prt(const char* x) { if constexpr(use_stdio) fprintf(stdio_out, "%s", x); else *out << x; }
	inline void prt(const string &x) { if constexpr(use_stdio) fprintf(stdio_out, "%s", x.c_str()); else *out << x; }
	template<typename T, typename enable_if<!use_stdio && is_integral<T>::value>::type* = nullptr> inline void prt(const T& x) { *out << x; }
	template<typename T, typename enable_if<is_container<T>::value>::type* = nullptr> inline void prt(const T& x);
	template<typename... Ts> inline void prt(const tuple<Ts...>& x);
	template<typename T, typename U> inline void prt(const pair<T, U>& x) { prt(x.first); prt(' '); prt(x.second); }
	template<typename T, typename enable_if<is_container<T>::value>::type* = nullptr> inline void prt(const T& x) {
	  if (x.begin() != x.end()) { prt(*x.begin()); for(auto it = x.begin(); ++it != x.end(); ) { prt(' '); prt(*it); } } }
	template<typename T, typename U, typename... Ts> inline void prt(T&& t, U&& u, Ts&&... ts) {
	  prt(forward<T>(t)); prt(' '); prt(forward<U>(u), forward<Ts>(ts)...); }
	template<typename... Ts> inline void prt(const tuple<Ts...>& x ) { static_assert(sizeof...(Ts) > 0);
	  constexpr auto apply_prt = [](auto&&... xs) { prt(xs...); }; apply(apply_prt, x); }
	inline void wt() { prt('\n'); }
	template<typename... Ts> inline void wt(Ts&&... ts) { prt(forward<Ts>(ts)...); wt(); }

	#ifdef MY_DEBUG_FLAG
	inline void enter_db() { if constexpr(use_stdio) stdio_out = stderr; else out = &cerr; }
	inline void leave_db() { if constexpr(use_stdio) stdio_out = stdout; else out = &cout; }
	inline void db() { enter_db(); prt('\n'); leave_db(); }
	template<typename... Ts> inline void db(Ts&&... ts) { enter_db(); prt(forward<Ts>(ts)...); wt(); leave_db(); }
	#define db(...) utils::db("Debug(", #__VA_ARGS__, ") == (", __VA_ARGS__, ")")
	#else
	#define db(...)
	#endif // define(MY_DEBUG_FLAG)
	constexpr int slen(char*s){ return (int) strlen(s); }
	template<typename T, typename U, typename enable_if<is_container<T>::value>::type* = nullptr> inline T& resize(T& x, U n) { 
	  x.resize(n); return x; }
	void flush() { if constexpr(use_stdio) fflush(stdout); else cout << std::flush; }
} using utils::rd, utils::prt, utils::wt, utils::slen, utils::resize, utils::flush;

#define pb emplace_back
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 1e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 998244353;

// it is better to keep them all balanced in groups
// for a fixed k we remove the k greatest value which are going to be the
// mimic chests, and then we divide the ramaining ones into n-k groups
// and it is always optimal to place them in the most spread out way
// possible, with the n-k first values appearing only one, the second n-k
// values appearing twice, and so on until we reach the end.
// if we go looking those values we'll get a final complexity of n ln n

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

void add_self(int& x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}

int sub(int a, int b) {
	int c = a - b;
	if(c < 0) c += mod;
	return c;
}

int n, inv;
vi a, pref, ans;

int main() {
	rd(n); rd(resize(a, n));
	inv = power(n, mod-2);

	sort(a.rbegin(), a.rend());

	pref = a;
	rep(i,1,n) add_self(pref[i], pref[i-1]);

	auto interval = [](int l, int r) {
		return sub(pref[min(r, n-1)], pref[l-1]);
	};

	rep(i,1,n) {
		int cur = 0;
		for(int k = i, cnt = 1; k < n; k += i, cnt++) {
			add_self(cur, (int)((1ll * cnt * interval(k, k+i-1)) % mod)); 
		}
		ans.pb((int)(1ll*cur*inv%mod));
	}
	wt(ans, 0);
}
