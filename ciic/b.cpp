#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back
#define sz(a) (int)((a).size())
#define all(a) (a).begin(), (a).end()

constexpr int maxn = 4e6+10;

int f[maxn];

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) {
			f[i] = i;
			if(1ll * i * i > maxn) continue;
			for(int j = i*i; j < maxn; j += i)
				if(!f[j]) f[j] = i;
		}
	}
}

vector<pii> dv(int n) {
	vector<pii> ans;
	while(n > 1) {
		if(ans.size() && ans.back().first == f[n])
			++ans.back().second;
		else ans.pb({f[n], 1});
		n /= f[n];
	}
	return ans;
}

long long choose2(int v) { return 1ll * v * (v-1) / 2; }

int pot[maxn];

int main() {
	sieve();
	int T; scanf("%d", &T);
	while(T--) {
		int n; scanf("%d", &n);
		long long ans = 0;
		vector<pii> aaa = dv(n);

		if(sz(aaa) == 1) {
			int pr = aaa[0].first, k = aaa[0].second;

			pot[0] = 1;
			for(int i = 1; i <= k; i++)
				pot[i] = pot[i-1] * pr;
			
			int sim = n / pr, nao = n - sim;
			ans = choose2(nao) + nao + 1ll * sim * nao + choose2(sim) + sim;

			vector<int> qtd;
			int tot = 0;
			
			for(int i = k; i >= 1; i--) {
				int aq = (n / pot[i]) - tot;
				tot += aq;
				qtd.pb(aq);
			}
			reverse(all(qtd));

			for(int i = 0; i < k; i++) {
				for(int j = i+1; j < k; j++)
					if(i + j + 2 > k) ans -= 1ll * qtd[i] * qtd[j];
				if(i+i+2 > k) ans -= qtd[i] + choose2(qtd[i]);
			}
		} else if(n <= 40) {
			for(int i = 1; i <= n; i++)
				for(int j = i; j <= n; j++)
					if(1ll * __gcd(i, n) * __gcd(j, n) == __gcd(1ll * i * j, 1ll * n))
						ans++;
		}
		else if(sz(aaa) == 2) {
			int p1 = aaa[0].first, p2 = aaa[1].first;
			// printf("a %d %d %d %d\n", n, p1, p2, p1*p2);
			vector<int> td;
			for(int x = p1; x <= n; x += p1)
				td.pb(x);
			for(int x = p2; x <= n; x += p2)
				td.pb(x);
			std::sort(all(td));
			td.resize(unique(all(td)) - td.begin());
			// for(int x : td)
			// 	printf("%d ", x);
			// puts("\n");
			ans = choose2(n) + n;
			for(int i = 0; i < sz(td); i++)
				for(int j = i; j < sz(td); j++)
					if(1ll * __gcd(td[i], n) * __gcd(td[j], n) != __gcd(1ll * td[i] * td[j], 1ll * n))
						--ans;
		}

		printf("%lld\n", ans);
	}
}