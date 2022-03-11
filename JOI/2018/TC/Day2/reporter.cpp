#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int maxn = 5e5+10;

int d[maxn], qtd[maxn];

int32_t main() {
	int n, q; scanf("%lld %lld", &n, &q);
	d[0] = 1;
	for(int i = 1; i <= n; i++)
		scanf("%lld", d+i);

	vector<int> st; st.push_back(0);
	for(int i = 1; i <= n; i++) {
		if(d[st.back()] < d[i])
			st.push_back(i);
	}

	qtd[0] = 1;
	for(int i = 1; i < st.size(); i++) {
		int last = st[i-1], aq = st[i];
		qtd[st[i]] = ((d[st[i]] + qtd[st[i-1]] - 1) / qtd[st[i-1]]) * qtd[st[i-1]];
	}

	for(int i = 1; i <= n; i++)
		if(!qtd[i]) qtd[i] = qtd[i-1];

	for(int i = 0; i < q; i++) {
		int t, L, R; scanf("%lld %lld %lld", &t, &L, &R);

		if(t < L) { puts("0"); continue; }

		int l = 0, r = n, GeqL = -1; // quero o primeiro cara maior ou igual a l
		while(l <= r) {
			int m = (l+r) >> 1;
			int pos = t - (t % qtd[m]) - m;
			if(pos >= L) GeqL = m, l = m+1;
			else r = m-1;
		}

		if(t <= R) { printf("%lld\n", GeqL+1); continue; }

		l = 0, r = n;
		int GR = 0;
		while(l <= r) {
			int m = (l+r) >> 1;
			int pos = t - (t % qtd[m]) - m;
			if(pos > R) GR = m, l = m+1;
			else r = m-1;
		}

		printf("%lld\n", GeqL - GR);
	}
}
