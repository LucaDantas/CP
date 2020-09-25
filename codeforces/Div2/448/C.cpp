#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;
constexpr int mod = 1e9+7;

int tam;

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

vector<int> base;

int get(int x) {
	for(auto v : base)
		x = min(x, x^v);
	return x;
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
		int x = get(a);
		if(x) base.push_back(x);
	}
	printf("%d\n", power(2, n - (int)base.size()) - 1);
}