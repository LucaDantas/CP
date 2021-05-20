#include <bits/stdc++.h>
using namespace std;

mt19937 rng(random_device{}());

int rnd(int x) { return (int)(rng() % x + x) % x; }

int rnd(int l, int r) { return l + rnd(r-l+1); }

int a[100000], b[100000];

int main() {
	int n = 10;
	printf("%d 1\n", n);
	for(int i = 1; i <= n; i++) {
		a[i] = rnd(1, 1000000000);
		b[i] = a[i] + i;
		printf("%d ", a[i]);
	}
	puts("");
	for(int i = 1; i <= n; i++)
		printf("%d ", b[i]);
	puts("");
}
