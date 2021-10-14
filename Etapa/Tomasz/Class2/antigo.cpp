#include <cstdlib>
#include <cstdio>

constexpr int maxn = 1<<20, lim = 1000, ver = 1000000;

int mark[maxn];

void printar(int a, int b, int c) {
	printf("%d\n", a+b+c+5);
	puts("1 2\n2 3\n3 4\n4 5");
	for(int i = 1; i <= a; i++)
		printf("1 %d\n", 5+i);
	for(int i = 1; i <= c; i++)
		printf("3 %d\n", 5+a+i);
	for(int i = 1; i <= b; i++)
		printf("5 %d\n", 5+a+c+i);
	exit(0);
}

int f[maxn];

void sieve() {
	f[1] = 1;
	for(int i = 2; i < maxn; i++)
		if(!f[i]) for(int j = i; j < maxn; j += i) f[j] = i;
}

void qtd(int v) {
	int aq = 0;
	while(v > 1) aq += f[v], v /= f[v];
	printf(" == %d\n", aq);
}

int main() {
	sieve();
	// int quero; scanf("%d", &quero);
	for(int a = 0; a < lim; a++)
		for(int b = 0; a+b < lim; b++)
			for(int c = 0; a+b+c+5 <= lim && a*b*(c+2) + (c+1) * (a+b) + c < maxn; c++) {
				mark[a*b*(c+2) + (c+1) * (a+b) + c] = 1;
				// if(a*b*(c+2) + (c+1) * (a+b) + c == quero) printar(a, b, c);
			}
	int errados = 0;
	for(int i = 1; i <= ver; i++)
		// if(!mark[i]) printf("%d ", i), errados++;
		if(!mark[i]) printf("%d ", i), errados++, qtd(i);
	putchar('\n');
	printf("errados == %d\n", errados);
	// qtd(100);
}
