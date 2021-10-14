#include <cstdlib>
#include <cstdio>

constexpr int maxn = 1<<25, lim = 281, ver = maxn-1;

int mark[maxn];

/* int f[maxn];

void sieve() {
	f[1] = 1;
	for(int i = 2; i < maxn; i++)
		if(!f[i]) for(int j = i; j < maxn; j += i) f[j] = i;
}

void qtd(int v) {
	int aq = 0;
	while(v > 1) aq += f[v], v /= f[v];
	printf(" == %d\n", aq);
} */

int main() {
	// sieve();
	// int quero; scanf("%d", &quero);
	for(int d = 0; d < lim; d++)
		for(int a = 0; a+d < lim; a++)
			for(int b = 0; a+b+d < lim; b++)
				for(int c = 0; a+b+c+d+7 <= lim && 1ll*d*((a+1)*b*(c+2) + (c+1) * ((a+1)+b) + c) + a*b*(c+2) + (c+1) * (a+b) + c < maxn; c++) {
					mark[1ll*d*((a+1)*b*(c+2) + (c+1) * ((a+1)+b) + c) + a*b*(c+2) + (c+1) * (a+b) + c] = 1;
					// if(1ll*d*((a+1)*b*(c+2) + (c+1) * ((a+1)+b) + c) + a*b*(c+2) + (c+1) * (a+b) + c == quero) printar(a, b, c, d);
				}
	int errados = 0;
	for(int i = 1; i <= ver; i++)
		if(!mark[i]) printf("%d ", i), errados++;
	putchar('\n');
	printf("errados == %d\n", errados);
}
