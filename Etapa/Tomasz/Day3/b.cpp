#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1009;
constexpr int maxn = 2e6+10;

int pot[maxn], fat[maxn];

int main() {
	int n; cin >> n;
	string s; cin >> s;
	pot[0] = fat[0] = 1;
	for(int i = 1; i < maxn; i++)
		pot[i] = pot[i-1] * 10 % mod, fat[i] = fat[i-1] * i % mod;
	int hash = 0;
	vector<int> bruh;
	for(int i = 0; i < (int)s.size(); i++)
		if(s[i] == '?') bruh.push_back(i);
		else hash += pot[(int)s.size() - i - 1] * (s[i]-'0'), hash %= mod;
	int k = (int)bruh.size(), pos = (int)(s.size()) - bruh.back() - 1;
	for(int a = 0; a < 10; a++)
		for(int b = 0; b < (k >= 2 ? 10 : 1); b++)
			for(int c = 0; c < (k == 3 ? 10 : 1); c++)
				if((hash + pot[pos] * a + pot[pos+1] * b + pot[pos+2] * c) % mod == fat[n]) {
					if(k == 1) printf("%d\n", a);
					else if(k == 2) printf("%d%d\n", b, a);
					else if(k == 3) printf("%d%d%d\n", c, b, a);
				}
}
