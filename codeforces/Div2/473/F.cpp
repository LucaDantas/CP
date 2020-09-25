#include<bits/stdc++.h>
using namespace std;

using piii = pair<pair<int, int>,int>;

constexpr int maxn = 1e5+10;
constexpr int mod = 1e9+7;

int a[maxn], resp[maxn];

vector<int> x;

int get(int v) {
	for(auto it : x)
		v = min(v, v^it);
	return v;
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	vector<piii> query(q);
	int cnt = 0;
	for(auto& it : query)
		scanf("%d %d", &it.first.first, &it.first.second), it.second = cnt++;
	sort(query.begin(), query.end());
	int ans = 1;
	for(int i = 1, ptr = 0; i <= n; i++) {
		if(get(a[i]) == 0) ans *= 2, ans %= mod;
		else x.push_back(get(a[i]));
		for(; ptr < q && query[ptr].first.first == i; ptr++)
			if(get(query[ptr].first.second) == 0) resp[query[ptr].second] = ans;
			else resp[query[ptr].second] = 0;
	}
	for(int i = 0; i < q; i++)
		printf("%d\n", resp[i]);
}