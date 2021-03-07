#include<cstdio>

int gcd(int a, int b) { return !b?a:gcd(b, a%b); }

int main() {
	int ans = 0, a[6], b[6];
	for(int i = 0; i < 6; i++)
		scanf("%d", &a[i]);
	for(int i = 0; i < 6; i++)
		scanf("%d", &b[i]);
	for(int i = 0; i < 6; i++) 
		for(int j = 0; j < 6; j++)
			if(a[i]>b[j]) ++ans;
	printf("%d/%d\n", ans/gcd(ans, 36), 36/gcd(ans, 36));
}