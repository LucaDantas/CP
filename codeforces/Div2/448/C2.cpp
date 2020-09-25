#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;
constexpr int mod = 1e9+7;

int tam, ans;

vector<int> pr;

void calc() {
	for(int i = 2; i <= 70; i++) {
		bool ok = 1;
		for(int j = 2; j < i; j++)
			if(!(i%j)) {ok = 0; break;}
		if(ok)
			pr.push_back(i);
	}
	tam = (int)pr.size();
}

int base[20];

void get(int x) {
	for(int i = 19; i >= 0; i--) {
		if(!(x&(1<<i))) continue;
		if(!base[i]) {
			base[i] = x;
			ans++;
			return;
		} else x ^= base[i];
	}
}

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

int main() {
	calc();
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int val, a = 0; scanf("%d", &val);
		for(int j = 0; j < tam; j++)
			while(!(val%pr[j]))
				a ^= (1<<j), val /= pr[j];
		get(a);
	}
	printf("%d\n", power(2, n - ans) - 1);
}