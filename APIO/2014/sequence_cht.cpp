#include <bits/stdc++.h>
using namespace std;

long long dv(long long a, long long b) { return a / b - ((a^b)<0 && a%b); }

struct Line {
	long long a, b; int id;
	Line(long long _a, long long _b, int _id) : a(_a), b(_b), id(_id) {}
	long long intersect(Line L) { return dv(L.b-b, a-L.a); }
	long long eval(long long x) { return a*x + b; }
};


struct CHT {
	deque<Line> cht;
	void add(Line L) {
		if(cht.size() && cht.front().a == L.a) {
			if(cht.front().b > L.b) return;
			cht.pop_front();
		}
		while(cht.size() >= 2 && L.intersect(cht[1]) < L.intersect(cht[0])) // por algum motivo só passou com < (melhor usar double msm)
			cht.pop_front();
		cht.push_front(L);
	}
	Line query(int x) {
		while(cht.size() >= 2 && cht[ cht.size() - 2 ].eval(x) >= cht.back().eval(x))
			cht.pop_back();
		return cht.back();
	}
} cht;

constexpr int maxn = 2e5+10, maxk = 210;

int a[maxn];
long long suf[maxn];
long long dp[2][maxn];
int opt[maxk][maxn];

int32_t main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", a+i);
	
	// dp[i] = dp[j] + suf[i+1] * (suf[j+1] - suf[i+1])
	// dp[i] = dp[j] + {suf[j+1] * suf[i+1]} - (suf[i+1]^2)

	for(int i = n; i >= 1; i--)
		suf[i] = a[i] + suf[i+1];

	for(int i = 1; i <= k; i++) {
		cht.cht.clear();
		cht.add(Line(suf[1], 0, -1));
		
		for(int j = 1; j <= n; j++) {
			Line bom = cht.query(suf[j+1]);

			opt[i][j] = bom.id;
			dp[1][j] = bom.eval(suf[j+1]) - 1ll*suf[j+1]*suf[j+1];

			cht.add(Line(suf[j+1], dp[0][j], j));
		}

		for(int j = 1; j <= n; j++)
			dp[0][j] = dp[1][j], dp[1][j] = 0;
	}

	long long ans = 0;
	for(int j = 1; j < n; j++)
		if(dp[0][j] >= dp[0][ans]) ans = j;

	printf("%lld\n", dp[0][ans]);

	for(int i = 0; i < k; i++)
		printf("%lld ", ans), ans = opt[k-i][ans];
	puts("");
}
