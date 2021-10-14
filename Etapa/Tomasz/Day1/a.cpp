#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

pair<long long,long long> ans[maxn];

vector<pair<int,int>> qr;
queue<pair<long long,int>> q[2];

int cut = (int)((1ll << 30) - 1);

bool geq(long long a, long long b) { return (a >> 30) * (b & cut) > (b >> 30) * (a & cut); }
bool eq(long long a, long long b) { return (a >> 30) * (b & cut) == (b >> 30) * (a & cut); }

int main() {
	int n, x, z; scanf("%d %d %d", &n, &x, &z);
	int last; scanf("%d", &last);
	vector<pair<int,int>> bruh;
	for(int i = 1; i < n; i++) {
		int a; scanf("%d", &a);
		bruh.push_back({a-last, last});
		last = a;
	}
	sort(bruh.begin(), bruh.end(), [](const pair<int,int>& a1, const pair<int,int>& a2) {
		if(a1.first == a2.first) return a1.second < a2.second;
		return a1.first > a2.first;
	});
	for(auto pp : bruh)
		q[0].push({((1ll*pp.first) << 30) | 1, pp.second});

	for(int i = 0, k; i < z; i++)
		scanf("%d", &k), qr.push_back({k, i});
	sort(qr.begin(), qr.end());
	long long qtd = 0;
	int ptr = 0;
	while(qtd < qr.back().first && q[0].size() + q[1].size()) {
		int pega = -1;
		if(!q[0].size()) pega = 1;
		else if(!q[1].size()) pega = 0;
		else if(eq(q[0].front().first, q[1].front().first)) pega = q[0].front().second > q[1].front().second;
		else if(geq(q[0].front().first, q[1].front().first)) pega = 0;
		else pega = 1;

		assert(pega != -1);
		long long grp = q[pega].front().first, ini = q[pega].front().second;
		q[pega].pop();

		long long a = grp >> 30, b = grp & cut;

		while(ptr < z && qtd + b >= qr[ptr].first) {
			ans[qr[ptr].second] = {1ll * ini * (b << 1) + a + (a<<1) * (qr[ptr].first - qtd - 1), (b << 1)};
			++ptr;
		}
		qtd += b;
		q[1].push({(a << 30) | (b << 1), ini});
	}
	for(int i = 0; i < z; i++)
		printf("%lld/%lld\n", ans[i].first / __gcd(ans[i].first, ans[i].second), ans[i].second / __gcd(ans[i].first, ans[i].second));
}
