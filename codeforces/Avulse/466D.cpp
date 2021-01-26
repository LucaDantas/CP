#include<bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9+7;

int main() {
	int n, h, ligados = 0, ans = 1;
	scanf("%d %d", &n, &h);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		x = h - x;
		if(x < 0) {puts("0"); return 0;}
		if(x > ligados) ligados++;
		else if(x == ligados) ans = (int)((1ll * ans * (ligados+1)) % mod);
		else if(x < ligados) ans = (int)((1ll * ans * ligados) % mod), ligados--;
		ligados = min(ligados, n-i);
		if(ligados != x) {puts("0"); return 0;}
	}
	printf("%d\n", ans);
}