#include<cstdio>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;

constexpr int maxn = 1e5+10, mod = 1000000007;

#define ff first
#define l first
#define ss second
#define r second

using pii = pair<int,int>;

pii events[maxn];

int dp[maxn], pot[maxn];

FILE *in, *out;

int main() {
	in = fopen("help.in", "r");
	out = fopen("help.out", "w");
	pot[0] = 1;
	for(int i = 1; i < maxn; i++)
		pot[i] = 2*pot[i-1]%mod;
	int n; fscanf(in, "%d", &n);
	for(int i = 0; i < n; i++)
		fscanf(in, "%d %d", &events[i].ff, &events[i].ss);
	sort(events, events+n);
	priority_queue<pii, vector<pii>, greater<pii>> q;
	int sum = 0, removed = 0;
	for(int i = 0; i < n; i++) {
		while(q.size() && q.top().ff < events[i].l)
			++removed, q.pop();
		q.push({events[i].r, i});
		dp[i] = (sum + pot[removed]) % mod;
		sum += dp[i];
		sum %= mod;
	}
	fprintf(out, "%d\n", sum);
}