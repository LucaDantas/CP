#include <cstdio>
#include <vector>

constexpr int maxn = 1010, logn = 11;

int grp[maxn][logn], pot[logn];

int diff(int i, int j) {
	int ans = 1;
	for(; grp[i][ans] != grp[j][ans]; ans++);
	return ans;
}

int main() {
	int n, k, c = 2, val; scanf("%d %d", &n, &k);
	pot[0] = 1, pot[1] = k; val = k*k;
	for(; val < n; c++, val *= k) pot[c] = val;
	pot[c] = val;

	for(int depth = 1; depth < c; depth++)
		for(int i = 0; i < n; i++)
			grp[i][depth] = i / pot[depth];

	printf("%d\n", c);
	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)
			printf("%d ", diff(i, j));
	puts("");
}
