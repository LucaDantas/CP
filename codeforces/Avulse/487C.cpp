#include<bits/stdc++.h>
using namespace std;

bool prime(int n) {
	for(int j = 2; j*j <= n; j++)
		if(!(n%j)) return 0;
	return 1;
}

constexpr int maxn = 1e5+10;

int inv[maxn];

// I want to make the resulting sequence to look like 1, 2, 3, ... n-1, 0
// So what I do is take my inverse mod n and multiply it by the next value
// in the sequence (i+1), so what we get is: (i^-1)*(i+1) for every i
// We can see that this causes no collisions because using fermat's little
// theorem we can rewrite that as i^(p-2) * (i+1) == i^(p-1) + i^p-2 ==
// == 1 + i^-1, this way since we know that every modular inverse is unique
// we also know that every modular inverse + 1 is unique and then the problem's
// solved because the resulting sequence is clearly unique and contains every value

int main() {
	int n; scanf("%d", &n);
	if(n == 1) {puts("YES\n1"); return 0;}
	if(n == 4) {puts("YES\n1 3 2 4"); return 0;}
	if(!prime(n)) {puts("NO"); return 0;}
	puts("YES");
	inv[1] = 1;
	printf("1 2 ");
	for(int i = 2; i < n; i++) {
		inv[i] = n - (int)(1ll * (n/i) * inv[n%i] % n);
		printf("%d ", inv[i] + 1);
	}
	puts("");
}