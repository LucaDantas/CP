#include<bits/stdc++.h>
using namespace std;

long long mask[20][2]; // on and off

int main() {
	int n; scanf("%d", &n);
	if(n >= (1 << 6)) assert(0);
	for(int i = 0; (1<<i) <= n; i++) {
		vector<int> a, b;
		for(int pos = 1; pos <= n; pos++) {
			if(pos&(1<<i))
				a.push_back(pos);
			else
				b.push_back(pos);
		}
		int c = a.size();
		printf("? %d", c);
		for(auto it : a) printf(" %d", it);
		printf("\n"); fflush(stdout);
		scanf("%lld", &mask[i][1]);
		c = b.size();
		printf("? %d", c);
		for(auto it : b) printf(" %d", it);
		printf("\n"); fflush(stdout);
		scanf("%lld", &mask[i][0]);
	}
	// cerr << "FINAL\n\n";
	printf("!");
	for(int i = 1; i <= n; i++) {
		long long ans = 0;
		for(int pos = 0; (1<<pos) <= n; pos++) {
			if(i&(1<<pos))
				ans |= mask[pos][0];
			else
				ans |= mask[pos][1];
			// cerr << "ans == " << ans << ", i == " << i << ", pos == " << pos << endl;
			// cerr << ans << ' ' << pos << endl;
		}
		printf(" %lld", ans);
	}
	printf("\n");
}
