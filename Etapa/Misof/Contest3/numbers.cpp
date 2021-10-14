#include <bits/stdc++.h>
using namespace std;

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 3e5+10;

char s[maxn];

int cnt[30], pai[maxn][30], grandao[maxn];
long long dp[maxn][30], cost_letter[30], cost[30];

int main() {
	cost_letter[0] = 1;
	for(int i = 1; i < 26; i++)
		if(i&1) cost_letter[i] = cost_letter[i-1] * 5;
		else cost_letter[i] = cost_letter[i-1] * 2;
	int T; scanf("%d", &T);
	while(T--) {
		scanf(" %s", s);
		int n = (int)strlen(s);

		for(int i = 0; i <= n; i++)
			for(int j = 0; j < 30; j++)
				dp[i][j] = -inf, pai[i][j] = -1;
		dp[0][25] = 0;

		grandao[n] = 0;
		for(int i = n-1; i >= 0; i--)
			grandao[i] = max(grandao[i+1], s[i] != '?' ? s[i]-'A' : 0);

		int t = 1;
		for(int i = 0, j = 0; i < n; ++t, ++i) {
			memset(cnt, 0, sizeof cnt);
			memset(cost, 0, sizeof cost);
			stack<int> st;
			for(j = i; j < n && s[j] != '?'; j++) {
				++cnt[s[j]-'A'], cost[0] += cost_letter[s[j]-'A'];
				while(st.size() && st.top() < s[j]-'A')
					cost[0] -= 2*cost_letter[st.top()], --cnt[st.top()], st.pop();
				st.push(s[j]-'A');
			}

			for(int k = 1; k < 26; k++)
				cost[k] = cost[k-1] - 2*cnt[k-1]*cost_letter[k-1];
			i = j;
			if(i == n) {
				for(int k = 0; k < 26; k++)
					dp[t-1][k] += cost[0];
				break;
			}
			pair<long long, int> opt = {-inf, 0};
			for(int k = 25; k >= grandao[i]; k--) {
				opt = max(opt, {dp[t-1][k], k});
				pai[t][k] = opt.second;
				dp[t][k] = opt.first + cost[k] + cost_letter[k];
			}
		}

		--t;
		pair<long long, int> opt = {-inf, 0};
		for(int k = 0; k < 26; k++)
			opt = max(opt, {dp[t][k], k});
		int now = opt.second;
		for(int i = n-1; i >= 0; i--) {
			if(s[i] == '?') s[i] = (char)(now+'A'), now = pai[t][now], --t;
		}
		printf("%lld\n%s\n", opt.first, s);
	}
}