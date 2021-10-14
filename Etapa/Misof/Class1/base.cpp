#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 14;
constexpr int mod = 1000000007;

int cnt[5000], tot[5000];
std::array<int,maxn> estados[5000];
std::vector<int> depende[5000];

int t;

bool valid(std::array<int,maxn> sq) {
	for(int i = 1; i < maxn; i++)
		if((sq[i] && sq[i-1]) || (i>1 && sq[i] == sq[i-2] && sq[i] > 0))
			return 0;
	return 1;
}

bool ok(std::array<int,maxn> a, std::array<int,maxn> b) {
	for(int i = 0; i < maxn; i++)
		if((a[i] == 2 && b[i] != 1) || (b[i] == 1 && a[i] != 2) || (a[i] == 1 && b[i] == 2)) return 0;
	return 1;
}

int calc_cnt(std::array<int,maxn> sq) {
	int ans = 0;
	for(int i = 0; i < maxn; i++)
		ans += sq[i] == 1;
	return ans;
}

int calc_tot(std::array<int,maxn> sq) {
	int ans = 0;
	for(int i = 0; i < maxn; i++)
		ans += sq[i] == 2;
	return ans;
}

int pot[maxn+1];

int dp[5000][65][2];

inline void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

int main() {
	int r, c, b; scanf("%d %d %d", &r, &c, &b);
	if(r > c) swap(r, c);

	if(c == 1) {
		printf("%d\n", 1+!b);
		return 0;
	}

	pot[0] = 1;
	for(int i = 1; i <= maxn; i++)
		pot[i] = pot[i-1] * 3;

	for(int mask = 0; mask < pot[r]; mask++) {
		std::array<int,maxn> sq;
		for(int i = 0; i < maxn; i++)
			sq[i] = (mask / pot[i]) % 3;
		if(valid(sq)) {
			estados[t] = sq;
			cnt[t] = calc_cnt(sq);
			tot[t] = calc_tot(sq);
			++t;
		}
	}

	for(int i = 0; i < t; i++)
		for(int j = 0; j < t; j++)
			if(ok(estados[j], estados[i]))
				depende[i].push_back(j);

	for(int i = 0; i < t; i++)
		dp[i][cnt[i]][0] = 1;

	for(int i = 2; i < c; i++) {
		for(int mask = 0; mask < t; mask++) {
			for(int qtd = 0; qtd < 65; qtd++) {
				if(qtd < cnt[mask]) continue;
				for(int x : depende[mask])
					add(dp[mask][qtd][1], dp[x][qtd - cnt[mask]][0]);
			}
		}

		for(int mask = 0; mask < t; mask++)
			for(int qtd = 0; qtd < 65; qtd++)
				dp[mask][qtd][0] = dp[mask][qtd][1], dp[mask][qtd][1] = 0;
	}

	int ans = 0;
	for(int mask = 0; mask < t; mask++)
		for(int qtd = 0; qtd < 65; qtd++)
			if(qtd + tot[mask] >= b && qtd + tot[mask] < 65)
				add(ans, dp[mask][qtd][0]);

	printf("%d\n", ans);
}