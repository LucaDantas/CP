#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
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

void SOLVE() {
	int n, dist; scanf("%d %d", &n, &dist);
	vector<int> a(n);
	for(auto& it : a)
		scanf("%d", &it);
	ld pos_l = 0, pos_r = dist, tempo = 0;
	int ptr_l = 0, ptr_r = n-1, vel_l = 1, vel_r = 1;
	for(;;) {
		assert(ptr_l - ptr_r <= 2);
		// db(ptr_l, ptr_r);
		if(ptr_l == n) {
			ld tempo_encontro = (pos_r - pos_l) / (ld)(vel_r+vel_l);
			ld falta = (pos_r - (ld)a[ptr_r]) / (ld)(vel_r);
			if(tempo_encontro < falta) {
				// db("RESPOSTA");
				// db(tempo + tempo_encontro);
				cout << tempo + tempo_encontro << '\n';
				return;
			} else {
				tempo += falta;
				pos_l += falta * vel_l;
				pos_r -= falta * vel_r;
				vel_r++;
				ptr_r--;
			}
		}
		if(ptr_r == -1) {
			ld tempo_encontro = (pos_r - pos_l) / (ld)(vel_r+vel_l);
			ld falta = ((ld)a[ptr_l] - pos_l) / (ld)(vel_l);
			if(tempo_encontro < falta) {
				// db("RESPOSTA");
				// db(tempo + tempo_encontro);
				cout << tempo + tempo_encontro << '\n';
				return;
			} else {
				tempo += falta;
				pos_l += falta * vel_l;
				pos_r -= falta * vel_r;
				vel_l++;
				ptr_l++;
			}
		}
		ld tempo_encontro = (pos_r - pos_l) / (ld)(vel_r+vel_l);
		ld tempo_l = ((ld)a[ptr_l] - pos_l) / (ld)(vel_l);
		ld tempo_r = (pos_r - (ld)a[ptr_r]) / (ld)(vel_r);
		// db(tempo_encontro, tempo_l, tempo_r);
		if(tempo_encontro < tempo_l && tempo_encontro < tempo_r) {
			// db("RESPOSTA");
			// db(tempo + tempo_encontro);
			cout << tempo + tempo_encontro << '\n';
			return;
		} else {
			if(tempo_l < tempo_r) {
				tempo += tempo_l;
				pos_l += tempo_l * vel_l;
				pos_r -= tempo_l * vel_r;
				vel_l++;
				ptr_l++;
				// db(ptr_l, ptr_r, "a");
			} else {
				tempo += tempo_r;
				pos_l += tempo_r * vel_l;
				pos_r -= tempo_r * vel_r;
				vel_r++;
				ptr_r--;
				// db(ptr_l, ptr_r, "b");
			}
		}
	}
}

int main() {
	cout << fixed; cout << setprecision(12); cerr << fixed; cerr << setprecision(12);
	int t; scanf("%d", &t);
	while(t--) {
		SOLVE(); //return 0;	
	}
}



// if(ptr_l == n)
// 	{check(pos_l, vel_l, pos_r, vel_r, tempo); return;}
// if(ptr_r == n)
// 	{check(pos_l, vel_l, pos_r, vel_r, tempo); return;}
// if(1ll*(a[ptr_l]-pos_l)*vel_r <= 1ll*(rev_a[ptr_r]-pos_r)*vel_l) {
// 	ld add = (ld)((ld)a[ptr_l]-pos_l)/(ld)vel_l;
// 	if(1ll * pos_r + 1ll * vel_r*add + 1ll * pos_l + 1ll * vel_l*add >= dist)
// 		{check(pos_l, vel_l, pos_r, vel_r, tempo); return;}
// 	tempo += add;
// 	pos_l += vel_l*add;
// 	pos_r += vel_r*add;
// 	vel_l++;
// 	ptr_l++;
// } else {
// 	ld add = (ld)((ld)a[ptr_l]-pos_r)/(ld)vel_r;
// 	if(1ll * pos_r + 1ll * vel_r*add + 1ll * pos_l + 1ll * vel_l*add >= dist)
// 		{check(pos_l, vel_l, pos_r, vel_r, tempo); return;}
// 	tempo += add;
// 	pos_l += vel_l*add;
// 	pos_r += vel_r*add;
// 	vel_r++;
// 	ptr_r++;
// }