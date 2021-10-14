#include <bits/stdc++.h>
using namespace std;

using pii = pair<long long,int>;

#define pb push_back

constexpr int mod = 1e9+7, maxn = 5e6+10, inf = 0x3f3f3f3f;

int power(int b, long long e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

long long pos[maxn];
char val[maxn];

int f[maxn];

vector<int> pr;

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) {
			f[i] = i;
			pr.pb(i);
			if(1ll * i * i > maxn) continue;
			for(int j = i*i; j < maxn; j += i)
				if(!f[j]) f[j] = i;
		}
	}
}

vector<pii> dvs(long long n) {
	vector<pii> ans;
	for(int p : pr) {
		if(n == 1) break;
		int cnt = 0;
		while(n % p == 0) n /= p, cnt++;
		if(cnt) ans.pb({p, cnt});
	}
	if(n > 1) ans.pb({n, 1});
	return ans;
}

void brute(long long val, int i, int j, vector<long long>& td, const vector<pii>& base) {
	if(i == (int)(base.size())) return (void)(td.pb(val));
	if(j < base[i].second) brute(val * base[i].first, i, j+1, td, base);
	brute(val, i+1, 0, td, base);
}

map<long long, int> qtd;

int main() {
	long long n, m, nc, mc, n0, m0, MXsz;
	scanf("%lld %lld %lld %lld %lld %lld %lld", &n, &m, &nc, &mc, &n0, &m0, &MXsz);

	for(int i = 0; i < nc; i++) {
		for(int j = 0; j < mc; j++) {
			char c; scanf(" %c", &c);
			val[i*mc + j] = c;
			pos[i*mc + j] = (i * m + j);
		}
	}
	int tot = nc*mc;

	for(int i = 0; i < tot; i++) {
		for(int j = i+1; j < tot; j++) {
			if(val[i] == val[j]) qtd[abs(pos[i] - pos[j])]++;
			else qtd[abs(pos[i] - pos[j])] = -inf;
		}
	}

	int inv25 = power(25, mod-2);

	int ans = 0;

	long long last = 1;

	map<long long, int> de_vdd;

	for(auto it : qtd) {
		long long val = it.first, perde = it.second;
		fprintf(stderr, "db1 %lld %lld\n", val, perde);
		
		vector<pii> prs = dvs(it.first);
		vector<long long> dv;
			brute(1, 0, 0, dv, prs);
		for(long long x : dv)
			if(de_vdd[x] >= 0) de_vdd[x] += it.second;
	}
	de_vdd[MXsz+1] += 0;

	for(auto it : de_vdd) {
		long long val = it.first, perde = it.second;
		fprintf(stderr, "%lld %lld | %d\n", val, perde, tot);
		for(long long gld = last; gld < val; gld++)
			fprintf(stderr, "deu %lld\n", gld), add(ans, power(26, gld - tot));
		/* if(val > last) 
			add(ans, power(26, val - last + 1) * inv25 % mod * power(26, last - tot) % mod); */
		last = val + 1;

		if(val > MXsz) break;
		// if(perde >= 0) add(ans, power(26, val - tot + perde));
	}
	printf("%d\n", ans);
}
