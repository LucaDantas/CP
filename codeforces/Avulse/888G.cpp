#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using ll = long long;

#define ff first
#define ss second
#define pb push_back
#define sz(a) (int)(a.size())

constexpr int maxn = 2e5+10, inf = 0x3f3f3f3f;

int a[maxn], cnt;
int trie[maxn*30][2];

vector<int> val[maxn*30];

void add(int x) {
	int pos = 0;
	for(int l = 29; l >= 0; l--) {
		int b = (x&(1<<l)) > 0;
		if(!trie[pos][b])
			trie[pos][b] = ++cnt;
		pos = trie[pos][b];
		val[pos].pb(x);
	}
}

int check(int x, int change) {
	int ans = 0, pos = 0;
	for(int l = 29; l >= 0; l--) {
		int b = (x&(1<<l)) > 0;
		if((l == change && trie[pos][!b]) || !trie[pos][b])
			ans |= 1 << l, assert(trie[pos][!b]), pos = trie[pos][!b];
		else pos = trie[pos][b];
	}
	return ans;
}

ll solve(int pos, int b) {
	if(!trie[pos][0] && !trie[pos][1]) return 0;
	ll add = (trie[pos][0]?solve(trie[pos][0], b-1):0) +
		(trie[pos][1]?solve(trie[pos][1], b-1):0);
	int ans = inf, go;
	if(sz(val[trie[pos][0]]) < sz(val[trie[pos][1]]))
		go = trie[pos][0];
	else go = trie[pos][1];
	for(int x : val[go])
		ans = min(ans, check(x, b));
	if(!sz(val[go]))
		ans = 0;
	return 1ll*ans + add;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]), add(a[i]);
	printf("%lld\n", solve(0, 29));
}