#include <cstdio>
#include <cassert>
#include <cstring>

constexpr int maxn = 1e5+10;

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int l[maxn], r[maxn], n, x;

int query(int L) {
	printf("check %d %d\n", L, 100000000); fflush(stdout);
	char s[5]; scanf(" %s", s);
	return !strcmp(s, "Yes");
}

long long qtd(int val, int qtd) {
	// quero saber quantos pares existem com valores ate v
	long long ans = 0;
	for(int i = 0, ptr = x; i <= n; i++) {
		for(; ptr >= 0 && i + ptr * qtd >= val; ptr--);
		ans += max(0, min(r[i], ptr) - l[i] + 1);
	}
	return ans;
}

int main() {
	scanf("%d %d", &n, &x);
	for(int i = 0; i <= n; i++)
		r[i] = x;
	long long tot = 1ll*(n+1)*(x+1);
	int tt = 0;
	for(; tt < 40 && tot > 1; tt++) {
		int L = 0, R = 1e8, ans = -1;
		while(L <= R) {
			int m = (L+R) >> 1;
			if(qtd(m, tt) <= tot/2) ans = m, L = m+1;
			else R = m-1;
		}
		int q = query(ans); tot = 0;
		if(q) for(int i = n, ptr = 0; i >= 0; i--) for(l[i] = max(l[i], ptr); l[i] <= x && i + l[i] * tt < ans; l[i]++, ptr++);
		else for(int i = 0, ptr = x; i <= n; i++) for(r[i] = min(r[i], ptr); r[i] >= 0 && i + r[i] * tt >= ans; r[i]--, ptr--);
		for(int i = 0; i <= n; i++) tot += max(0, r[i] - l[i] + 1);
	}
	assert(tot == 1);
	for(int i = 0; i <= n; i++)
		if(l[i] == r[i]) printf("answer %d\n", i + tt * l[i]);
}
