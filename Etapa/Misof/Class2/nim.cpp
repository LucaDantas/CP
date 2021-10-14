#include <cstdio>

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		int val = 0;
		bool ok = 0;
		while(n--) { int v; scanf("%d", &v); val ^= v; ok |= v>1; }
		puts((ok && val) || (!ok && !val) ? "Haluc" : "Alla");
	}
}
