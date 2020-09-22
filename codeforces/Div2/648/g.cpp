#include<bits/stdc++.h>
using namespace std;

// I first made one that used the bitwise or of everyone that had at least one bit
// different from me, but on that variant I needed to make 2 * log(n)

// Leo said one that transposes every item into a 13-bit 6-on number, because we have
// 13 choose 6 > 1700 > 1000 possibilities, and every item has at least one different
// from me because nobody can be a subset from another because everyone has the same 
// number of bits on. We can just check for everyone the number all the bits that are off
// because we'll check everyone else, since there is no submasks of one another

constexpr int maxn = 1e3+10;

int numero[maxn];
long long mask[13];

int main() {
	int n; scanf("%d", &n);
	int cnt = 0;
	for(int mask = 1; mask < (1 << 13); mask++) {
		if(__builtin_popcount(mask) == 6)
			numero[++cnt] = mask;
		if(cnt == n) break;
	}
	// for(int i = 1; i <= n; i++)
	// 	printf("%d ", numero[i]);
	// puts("");
	
	for(int p = 0; p < 13; p++) {
		vector<int> a;
		for(int i = 1; i <= n; i++)
			if(numero[i]&(1<<p))
				a.push_back(i);
		if(!a.size()) continue;
		printf("? %d", (int)a.size());
		for(auto it : a) printf(" %d", it);
		puts(""); fflush(stdout);
		scanf("%lld", &mask[p]);
	}

	putchar('!');
	for(int i = 1; i <= n; i++) {
		long long ans = 0;
		for(int p = 0; p < 13; p++)
			if(!(numero[i]&(1<<p)))
				ans |= mask[p];
		printf(" %lld", ans);
	}
	puts("");
}
