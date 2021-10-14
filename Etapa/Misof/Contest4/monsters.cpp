#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;

int a[30][30];

char s[maxn];

int vivo[30];
bool mark[maxn];

bool safe(int pos) {
	bool ok = 1;
	for(int i = 0; i < 26; i++)
		ok &= !vivo[i] || a[pos][i];
	return ok;
}

int main() {
	int k, n; scanf("%d %d", &k, &n);
	for(int i = 0; i < k; i++) {
		for(int j = 0; j < k; j++) {
			char c; scanf(" %c", &c);
			a[i][j] = c-'0';
		}
	}
	scanf(" %s", s);
	vector<pair<int,int>> atv;
	for(int i = n-1; i >= 0; i--) {
		int c = s[i] - 'a', menor = c+1;
		for(int j = (int)(atv.size()) - 1; j >= 0; j--) {
			
		}
	}
}
