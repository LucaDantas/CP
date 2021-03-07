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

int n;
char a[maxn], b[maxn];

bool eq(char* k, char* l) {
	for(int i = 0; i < n; i++)
		if(k[i] != l[i]) return 0;
	return 1;
}

void add(char* s) {
	bool ok = 1;
	for(int i = n-1; i >= 0; i--) {
		if(ok) {
			if(s[i] == '1') s[i] = '0';
			else s[i] = '1', ok = 0;
		}
	}
}

int main() {
	scanf("%d", &n);
	scanf(" %s %s", a, b);
	if(eq(a, b)) return printf("%s\n", b), 0;
	if(a[0] == '0') {
		memset(a, '1', n*sizeof(char));
		printf("%s\n", a);
		return 0;
	}
	add(a);
	if(!eq(a, b)) b[n-1] = '1';
	printf("%s\n", b);
}
