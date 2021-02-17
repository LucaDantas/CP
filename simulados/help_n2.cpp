#include<cstdio>
#include<utility>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cassert>
using namespace std;

#define pb push_back

constexpr int maxn = 1e5+10, mod = 1000000007;

using pii = pair<int,int>;

FILE *in, *out;

struct Event {
	int l, r;
	bool operator<(Event a) {
		return r < a.r;
	}
} events[maxn];

inline void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

struct BIT
{
	int bit[maxn];
	void upd(int x, int v) {
		for(; x < maxn; x += x&-x)
			add(bit[x], v);
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x -= x&-x)
			add(ans, bit[x]);
		return ans;
	}
	int itv(int l, int r) {
		return query(r) - query(l-1); // se l == 0 retorna logo msm
	}
} bit[11]; // guarda pref da dp pra cada K

int dp[maxn][11], pot[maxn], fat[maxn], inv_fat[maxn];

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

void calc() {
	fat[0] = inv_fat[0] = pot[0] =  1;
	for(int i = 1; i < maxn; i++)
		fat[i] = (int)(1ll * i * fat[i-1] % mod),
		inv_fat[i] = power(fat[i], mod-2);
	for(int i = 1; i < maxn; i++)
		pot[i] = 2*pot[i-1]%mod;
}

int choose(int a, int b) {
	if(b > a) return 0;
	return (int)((1ll * fat[a] * inv_fat[a-b] % mod) * inv_fat[b] % mod);
}

int main() {
	calc();
	in = fopen("help.in", "r");
	out = fopen("help.out", "w");
	int n, K, ans = 0; fscanf(in, "%d %d", &n, &K);
	for(int i = 0; i < n; i++)
		fscanf(in, "%d %d", &events[i].l, &events[i].r);
	sort(events, events+n);
	for(int i = 0; i < n; i++) {
		// printf("%d %d\n", events[i].l, events[i].r);
		
		vector<pii> opa;
		int dentro = 0;
		for(int j = i-1; j >= 0 && events[j].r >= events[i].l; j--) {
			if(events[j].l >= events[i].l) ++dentro;
			else opa.pb({j, dentro});
		}

		for(int rmv = 0; rmv < (int)opa.size(); rmv++) {
			for(int k = 0; k <= K; k++) {
				add(dp[i][k], (int)(1ll*pot[opa[rmv].second]*dp[opa[rmv].first][k]%mod));
			}
		}

		// eu me colocando sozinho
		for(int k = 0; k <= K; k++) {
			// quantos eu boto em mim
			for(int j = 0; j+k <= K; j++) {
				// quantos eu pego do anterior
				add(dp[i][j+k], (int)(1ll*choose(j+k, j)*bit[j].query(events[i].l-1)%mod*pot[dentro]%mod));
			}
			add(dp[i][k], pot[dentro]);
		}

		for(int k = 0; k <= K; k++)
			bit[k].upd(events[i].r, dp[i][k]);
		// 	fprintf(stderr, "%d ", dp[i][k]);
		// fprintf(stderr, "\n\n");
		add(ans, dp[i][K]);
	}
	fprintf(out, "%d\n", ans);
	fprintf(stderr, "%d\n", ans);
}