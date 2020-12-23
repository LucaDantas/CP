#include<bits/stdc++.h>
using namespace std;

int b[30];

int main() {
	int n; long long k, t = 0; scanf("%d %lld", &n, &k);
	for(int i = 0; i < n-2; i++) {
		char c; scanf(" %c", &c);
		++b[c-'a']; t += (1<<(c-'a'));
	}
	char c; scanf(" %c", &c);
	k += (1<<(c-'a'));
	scanf(" %c", &c);
	k -= (1<<(c-'a'));
	if(k < 0) k = -k;
	for(int i = 29; i >= 0; i--) {
		while(b[i]--) {
			t -= 1<<i;
			if(k+(1<<i) <= t) k += 1<<i;
			else k -= 1<<i;
		}
	}
	puts(k?"No":"Yes");
}