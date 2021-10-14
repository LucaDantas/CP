#include <bits/stdc++.h>
using namespace std;

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

constexpr int maxn = 5e6+10;

int f[maxn];

vector<int> pr;

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i])
			f[i] = i, pr.pb(i);
		for(int j = 0; j < (int)pr.size() && pr[j] <= f[i] && 1ll*i*pr[j] < maxn; j++)
			f[i*pr[j]] = pr[j];
	}
}

map<long long, vector<long long>> dvs;

set<long long> st;

long long val[maxn], pre[maxn];

//const int sla = 25, linha = 1000/sla;
const int sla = 5, linha = 1000/sla;

int power(int b, int e, int mod) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

bool is_prime(long long vv) {
	for(int p : pr) {
		if(1ll * p * p > vv) break;
		if(vv % p == 0) { printf("%d -> ", p); return 0; }
	}
	return 1;
}

int main() {
	sieve();
	int n = sla*linha;
	long long m = 32425234582340;
	//long long m; scanf("%lld", &m);
	for(int i = 0; i < linha; i++)
		for(int j = 0; j < sla; j++)
			pre[i*sla + j] = m*i + j;

	int t = 0;
	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)
			val[t++] = abs(pre[i] - pre[j]), st.insert(val[t-1]);

	sort(val, val+t);
	t = (int)(unique(val, val+t)-val);
	


	long long a = m;
	for(int p : pr) {
		if(__gcd(a, (long long)p) == 1) {
			for(int b = -sla+1; b < sla; b++) {
				// ax + b === 0 mod p -> x === (-b) * a^(-1) mod p
				int rcr = (int)(1ll * (1ll*sla*p - b)%p * power((int)(a%p), p-2, p) % p);
				if(!rcr && !st.count(b)) rcr += p;
				while(rcr < linha) dvs[a*rcr + b].push_back(p), rcr += p;
			}
		} else {
			//printf(">%d\n", p);
			for(const long long& it : st)
				if(it % p == 0) dvs[it].pb(p);
		}
	}

	for(auto it : dvs) {
		assert(st.count(it.first));
		long long num = it.first;
		for(long long p : it.second)
			while(num % p == 0) num /= p;
		if(!is_prime(num)) { printf("%lld %lld\n", it.first, num); db(it.second) ;exit(0); }
	}
}
