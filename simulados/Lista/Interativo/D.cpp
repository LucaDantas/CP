#include<cstdio>
#include<vector>

constexpr int maxn = 2000;

bool mark[maxn];

bool query(int i) {
	printf("? %d\n", i); fflush(stdout);
	char c; scanf(" %c", &c);
	return c=='Y';
}

std::vector<std::vector<int>> solve(int l, int r, int k) {
	if(r - l + 1 == k) {
		// base case
		std::vector<std::vector<int>> block(2);
		for(int i = l; i <= r; i++) {
			block[i>(l+r)/2].push_back(i);
			mark[i] = query(i);
		}
		puts("R");
		return block;
	}

	// Fix the elements from the left block and try to mark
	// everyone from the right block
	int m = (l+r) >> 1, qtd = 2 * (r-l+1) / k, qtd2 = qtd>>1;
	std::vector<std::vector<int>> bl = solve(l, m, k), br = solve(m+1, r, k);
	for(int i = 0; i < qtd2; i++) {
		for(int j = 0; j < qtd2; j++) {
			for(int x : bl[i])
				query(x);
			for(int x : br[j])
				mark[x] |= query(x);
			puts("R");
		}
	}

	// that's what I'll return to my parent
	std::vector<std::vector<int>> block(qtd);
	for(int i = 0, ptr = l; i < qtd; i++)
		for(int j = 0; j < k/2; j++, ptr++)
			block[i].push_back(ptr);
	return block;
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	if(k > 1)
		solve(1, n, k);
	else // just brute force compare everyone
		for(int i = 1; i <= n; i++)
			for(int j = i+1; j <= n; j++)
				query(i), mark[j] |= query(j);
	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans += !mark[i];
	printf("! %d\n", ans);
}