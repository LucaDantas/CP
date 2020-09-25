#include<bits/stdc++.h>
using namespace std;

#define db(a) cout << a << '\n';

using piii = pair<pair<int, int>,int>;

constexpr int maxn = 1e5+10;
constexpr int maxl = 20;
constexpr int mod = 1e9+7;

int a[maxn], resp[maxn];

int base[maxl];

bool add(int v) {
	for(int i = 19; i >= 0; i--) {
		if(!(v&(1<<i))) continue;
		if(base[i] == -1) {
			base[i] = v;
			return 1;
		}
		v ^= base[i];
	}
	return 0;
}

bool check(int v) {
	for(int i = 19; i >= 0; i--) {
		if(!(v&(1<<i))) continue;
		if(base[i] == -1)
			return 1;
		v ^= base[i];
	}
	return 0;
}

int main() {
	memset(base, -1, sizeof base);
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
		if(!add(a[i])) ans *= 2, ans %= mod;
		for(; ptr < q && query[ptr].first.first == i; ptr++)
			if(check(query[ptr].first.second) == 0) resp[query[ptr].second] = ans;
			else resp[query[ptr].second] = 0;
	}
	for(int i = 0; i < q; i++)
		printf("%d\n", resp[i]);
}