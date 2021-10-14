#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e7+10;

struct DSU
{
	int pai[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = -1; }
	int find(int x) { return pai[x] < 0 ? x : pai[x] = find(pai[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(pai[a] > pai[b])
			swap(a, b);
		pai[a] += pai[b];
		pai[b] = a;
	}
} dsu;

bool mark[maxn];

int n, shift;

inline int linha(int x, int y, int z) { return x * (n+1) + y + shift*z; }
inline int coluna(int x, int y, int z) { return x * (n+1) + y + shift*(z+2); }

vector<int> aq;

char s[4][2010], gld[2010];

int main() {
	int q; scanf("%d %d", &n, &q);
	shift = (n+1) * (n+1);
	for(int i = 0; i < n; i++) {
		scanf(" %s", gld);
		for(int j = 0; j < n; j++) {
			// char c; scanf(" %c", &c);
			for(int k = 0; k < 2; k++) {
				if(gld[j] == 'A') {
					dsu.join(linha(i,j,k), coluna(i,j,!k));
					dsu.join(linha(i,j,k), coluna(i,j+1,!k));
					dsu.join(linha(i+1,j,k), coluna(i,j,!k));
					dsu.join(linha(i+1,j,k), coluna(i,j+1,!k));
				} else {
					dsu.join(linha(i,j,k), linha(i+1,j,!k));
					dsu.join(coluna(i,j,k), coluna(i,j+1,!k));
				}
			}
		}
	}

	while(q--) {
		bool ok = 1;
		for(int bruh = 0; bruh < 4; bruh++)
			scanf(" %s", s[bruh]);
		for(int i = 0; i < n && ok; i++) {
			aq.pb(dsu.find(linha(0,i,s[0][i]-'0')));
			mark[aq.back()] = 1;
			ok &= !mark[dsu.find(linha(0,i,!(s[0][i]-'0')))];
		}
		for(int i = 0; i < n && ok; i++) {
			aq.pb(dsu.find(linha(n,i,s[1][i]-'0')));
			mark[aq.back()] = 1;
			ok &= !mark[dsu.find(linha(n,i,!(s[1][i]-'0')))];
		}
		for(int i = 0; i < n && ok; i++) {
			aq.pb(dsu.find(coluna(i,0,s[2][i]-'0')));
			mark[aq.back()] = 1;
			ok &= !mark[dsu.find(coluna(i,0,!(s[2][i]-'0')))];
		}
		for(int i = 0; i < n && ok; i++) {
			aq.pb(dsu.find(coluna(i,n,s[3][i]-'0')));
			mark[aq.back()] = 1;
			ok &= !mark[dsu.find(coluna(i,n,!(s[3][i]-'0')))];
		}
		puts(ok ? "YES" : "NO");
		for(const int& x : aq)
			mark[x] = 0;
		aq.clear();
	}
}