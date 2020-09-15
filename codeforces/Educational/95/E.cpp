#include<bits/stdc++.h>
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

#define all(a) a.begin(), a.end()
#define sz(a) (int)(a.size())

constexpr int mod = 998244353;
constexpr int maxn = 2e5+10;

int fat[maxn], inv_fat[maxn], inv[maxn];

// m mod i = m - (m/i)*i
// i^(-1) === - (m/i) * (m%i)^(-1) mod m

void calc() {
	inv[1] = fat[1] = fat[0] = inv_fat[0] = inv_fat[1] = 1;
	for(int i = 2; i < maxn; i++) {
		inv[i] = (int)(mod - (1ll * (mod/i) * inv[mod%i] % mod));
		fat[i] = (int)(1ll * fat[i-1] * i % mod);
		inv_fat[i] = (int)(1ll * inv_fat[i-1] * inv[i] % mod);
	}
}

int choose(int a, int b) {
	// a choose b
	assert(a >= b);
	return (int)((1ll * fat[a] * inv_fat[b] % mod) * inv_fat[a-b] % mod);
}

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

int main() {
	calc();
	int n, m; scanf("%d %d", &n, &m);
	vector<int> d(n), pref(n+1), suf(n+1);

	for(auto& it : d)
		scanf("%d", &it);
	sort(all(d));

	for(int i = 1; i <= n; i++) {
		pref[i] = (pref[i-1] + d[i-1]) % mod;
		suf[i] = (suf[i-1] + d[n-i]) % mod;
	}

	for(int i = 1; i <= n; i++) {
		pref[i] = (int)(1ll * pref[i] * inv[i] % mod);
		suf[i] = (int)(1ll * suf[i] * inv[i] % mod);
	}

	while(m--) {
		auto bs = [&](int val) {
			int l = 0, r = sz(d), ans = -1;
			while(l <= r) {
				int mid = (l+r) >> 1;
				if(d[mid] >= val) {
					r = mid-1;
				} else {
					ans = mid;
					l = mid+1;
				}
			}
			return ans+1;
		};
		int a, b; scanf("%d %d", &a, &b);
		int menores = bs(b), maiores = n - menores;
		int ev_maiores = suf[maiores], ev_menores = pref[menores];
		if(maiores < a) {puts("0"); continue;}
		// int p = 0, q = 0;
		int ans = (int)(1ll * ev_maiores * (maiores - a) % mod);
		
		// Jeito lento mas certo de contar o dano dos menores

		// for(int i = maiores-a; i <= n - a; i++) {
		// 	// i == quantidade de caras que vão bater
		// 	int pos = (int)(1ll * choose(i, maiores - a) * choose(n-i-1, a-1) % mod); // contando o número de possibilidades
		// 	int cima = (int)((1ll * ev_menores * (i - maiores + a) % mod) * pos % mod);
		// 	p += cima; if(p >= mod) p -= mod;
		// 	q += pos; if(q >= mod) q -= mod;
		// }
		// ans += (int)(1ll*p*power(q, mod-2)%mod); 
		// if(ans >= mod) ans -= mod;

		// Jeito rápido de contar os menores
		// A gente pensa nos espaçoes entre os grandes, e cada menor tem exatamente a mesma
		// probabilidade de cair em cada espaço, e pra contar tem que cair depois do a-esimo

		ans += (int)((1ll * ev_menores * menores % mod) * (1ll * (maiores + 1 - a) * inv[maiores+1] % mod) % mod);
		if(ans >= mod) ans -= mod;

		printf("%d\n", ans);
	}
}