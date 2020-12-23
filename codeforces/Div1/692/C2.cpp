#include<bits/stdc++.h>
using namespace std;

int b[64];

int main() {
	int n; long long k, t = 0; scanf("%d %lld", &n, &k);
	for(int i = 0; i < n-2; i++) {
		char c; scanf(" %c", &c);
		++b[c-'a'+1]; k += (1<<(c-'a'));
	}
	char c; scanf(" %c", &c);
	k += (1<<(c-'a'));
	scanf(" %c", &c);
	k -= (1<<(c-'a'));
	if(k < 0) {puts("No"); return 0;}
	for(int i = 0; i <= 60; i++) {
		if(k&(1ll<<i)) {
			if(!b[i]) {puts("No"); return 0;}
			--b[i];
		}
		b[i+1] += b[i] >> 1;
	}
	puts("Yes");
}