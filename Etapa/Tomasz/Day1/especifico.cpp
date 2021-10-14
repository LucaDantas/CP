#include <cstdio>

int t=1, p1 = 12, p2 = 7, n = 15;

void chain(int pai, int qtd) {
	int aq = ++t;
	printf("%d %d\n", pai, aq); 

	for(int i = 1; i < qtd; i++)
		printf("%d %d\n", aq, ++t);
}

void direto(int pai, int qtd) { for(int i = 0; i < qtd; i++) printf("%d %d\n", pai, ++t); }

int main() {
	printf("%d 3\n", n);
	printf("%d %d %d\n", 1, p1, p2);
	chain(1, 3);
	chain(1, 1);
	printf("1 %d\n", ++t);
	printf("%d %d\n", t, t+1), ++t;
	p1 = t;
	direto(p1, 3);
	printf("1 %d\n", ++t);
	printf("%d %d\n", t, t+1), ++t;
	p2 = t;
	direto(p2, 3);
}
