#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

long long a[maxn]; // quantos caras precisam passar por cada pos

vector<pair<int,int>> opa[maxn];

bool check(long long qtd_mov, long long M, int sz) {
	vector<long long> mov(sz+1);
	for(int i = 1; i <= sz; i++)
		mov[i] = (a[i] + qtd_mov - M + 1) / 2;

	priority_queue<pair<int, int>> q;
	vector<long long> add_lazy(sz+1);

	long long usados = 0, lazy = 0;
	for(int i = 1; i <= sz; i++) {
		for(pair<int,int> par : opa[i])
			q.push(par);
		
		lazy += add_lazy[i];
		mov[i] += lazy;

		while(mov[i] > 0) {
			if(!q.size() || q.top().first <= i) return 0; // não da pra fazer
			pair<int,int> usar = q.top();
			q.pop();
			if(usar.second > mov[i])
				q.push({usar.first, usar.second - mov[i]}), usar.second = (int)mov[i];

			mov[i] -= usar.second;
			lazy -= usar.second;
			add_lazy[usar.first] += usar.second;
			usados += usar.second;
		}
	}

	return usados <= qtd_mov;
}

int main() {
	int sz, n; scanf("%d %d", &sz, &n);
	for(int i = 0; i < n; i++) {
		int l, r, c;
		scanf("%d %d %d", &l, &r, &c);
		if(l > r) swap(l, r);
		a[l] += c, a[r] -= c;
		opa[l].push_back({r, c});
	}

	long long mx = 0;
	for(int i = 1; i <= sz; i++)
		a[i] += a[i-1], mx = max(mx, a[i]);
	
	long long L = 0, R = mx, ans = -1;
	while(L <= R) {
		long long M = (L+R) >> 1;
		long long qtd_mov = mx - M;
		// a[i] + qtd_mov - 2*mov[i] <= M
		// 2*mov[i] >= a[i] + qtd_mov - M
		// mov[i] >= ceiling( (a[i] + qtd_mov - M) / 2 )
		// mov[i] >= (a[i] + qtd_mov - M + 1) / 2
		if(check(qtd_mov, M, sz) || check(qtd_mov+1, M, sz))
			ans = M, R = M-1;
		else
			L = M+1;
	}
	printf("%lld\n", ans);
}
