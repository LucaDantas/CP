#include "wiring.h"

constexpr int maxn = 1e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

long long dp[maxn], new_dp[maxn]; // quantos passam do block anterior

std::vector<std::vector<int>> blocks;

inline long long min(long long a, long long b) { return a < b ? a : b; }

long long min_total_length(std::vector<int> r, std::vector<int> b) {
	std::vector<int> red;
	int ptr = 0;
	for(int i = 0; i < (int)r.size(); i++) {
		std::vector<int> aq;
		for(; ptr < (int)b.size() && b[ptr] < r[i]; ptr++)
			aq.push_back(b[ptr]);
		if(aq.size()) {
			if(red.size()) blocks.push_back(red);
			blocks.push_back(aq);
			red = {r[i]};
		} else red.push_back(r[i]);
	}
	if(red.size()) blocks.push_back(red);
	if(ptr < (int)b.size()) {
		std::vector<int> sobrou;
		for(; ptr < (int)b.size(); ptr++)
			sobrou.push_back(b[ptr]);
		blocks.push_back(sobrou);
	}

	for(int i = 0; i < maxn; i++)
		dp[i] = new_dp[i] = inf;
	dp[0] = 0;
	int n = (int)blocks.size();
	long long c_ovf = inf;

	int last_sz = 0;
	for(int i = 0; i < n; i++) {
		std::vector<int> aq = blocks[i];
		std::vector<long long> soma_pos(aq.size());
		int m = (int)aq.size();
		soma_pos[m-1] = aq[m-1];
		for(int j = m-2; j >= 0; j--)
			soma_pos[j] = soma_pos[j+1] + aq[j];

		long long ans = inf, dist = 0;
		for(int j = 0; j < m; j++) {
			// passando a partir do cara j
			ans = min(ans + c_ovf, dp[j]);
			int qtd = m-j;
			new_dp[qtd] = ans + (i<n-1 ? (long long)blocks[i+1][0]*qtd - soma_pos[j] : 0) + dist;
			dist += aq[j] - aq[0];
		}
		// não passar ngm
		ans = min(ans + c_ovf, dp[m]);
		new_dp[0] = ans + dist; // todo mundo liga pra trás

		for(int j = 0; j <= last_sz+1; j++)
			dp[j] = inf;
		for(int j = m; j >= 1; j--)
			dp[j] = min(dp[j+1], new_dp[j]), new_dp[j] = inf;
		dp[0] = new_dp[0]; new_dp[0] = inf;

		last_sz = m;
		if(i < n-1)
			c_ovf = blocks[i+1][0] - aq.back();
	}

	return dp[0];
}
