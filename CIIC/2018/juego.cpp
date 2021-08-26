#include <cstdio>

constexpr int maxn = 1e5+10;

int max(int a, int b) { return a > b ? a : b; }
int a[maxn][2], ans[2];

int main() {
	int n; scanf("%d", &n);
	for(int j = 0; j < 2; j++) for(int i = 0; i < n; i++)
		scanf("%d", &a[i][j]);
	for(int i = 0; i < n; i++) {
		ans[0] += max(a[i][0] + a[i][1], -a[i][0] - a[i][1]);
		ans[1] += max(a[i][0] - a[i][1], -a[i][0] + a[i][1]);
	}
	printf("%d\n", max(ans[0], ans[1]));
}
