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
constexpr int MAXN = 2e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int tree[4*MAXN];

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = inf;
		return;
	}
	int m = (i+j) >> 1;
	build(2*node, i, m);
	build(2*node+1, m+1, j);
	tree[node] = inf;
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		tree[node] = val;
		return;
	}
	int m = (i+j) >> 1;
	if(pos <= m) update(2*node, i, m, pos, val);
	else update(2*node+1, m+1, j, pos, val);
	tree[node] = min(tree[2*node], tree[2*node+1]);
}

int query(int node, int i, int j, int l, int val) {
	if(j < l) return inf;
	if(tree[node] > val) return inf;
	if(i == j) return i;
	
	int m = (i+j) >> 1;
	int p1 = query(2*node, i, m, l, val);
	if(p1 == inf) return query(2*node+1, m+1, j, l, val);
	else return p1;
}

int main() {
	int n, q;
	rd(n, q);

	build(1,1,n);

	while(q--) {
		char t;
		int a, b;
		rd(t, a, b);
		if(t == 'M') {
			update(1, 1, n, b, a);
		}
		else {
			int ans = query(1, 1, n, b, a);
			wt(ans==inf?-1:ans);
		}
	}
}
