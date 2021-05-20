#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e4+10;

int dp[maxn], vivo[maxn]; // se i for o ultimo cada pessoa morre ou vive?

int main() {
	int n, k; scanf("%d %d", &n, &k);
	vivo[0] = 1;
	int mortos = 0;
	for(int i = 1; i <= n; i++) {
		int tem = 1 + mortos + k;
		
		// I claim that everyone from a different parity is buyable
		// So I can simply assume that there always is enough people
		// that I can buy
		if(tem >= (i+1)/2) {
			dp[i] = k - ((i+1)/2 - (1 + mortos));
			vivo[i] = 1;
			mortos = 0;
		}
		else ++mortos;
	}

	for(int i = n; i >= 1; i--)
		if(vivo[i]) return printf("%d %d\n", n-i, dp[i]), 0;
}