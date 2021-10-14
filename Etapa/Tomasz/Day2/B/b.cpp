#include <cstdio>

int main() {
	int K; scanf("%d", &K);
	if(!K) { puts("1\n#"); return 0;}
	if(K == 1) { puts("1\n."); return 0;}
	printf("%d\n", K);
	for(int i = 0; i < K; i++)
		putchar('.');
	putchar('\n');
	for(int i = 0; i < K; i++)
		putchar('.');
	putchar('\n');
	for(int rep = 2; rep < K; rep++) {
		for(int i = 0; i < K-1; i++)
			putchar('#');
		putchar('.');
		putchar('\n');
	}
}
