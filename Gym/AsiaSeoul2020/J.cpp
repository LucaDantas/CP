#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 510;

int used[maxn], n;

bitset<maxn> base[maxn], bit, sla, usados[maxn];

void insert(int id) {
	for(int l = n-1; l >= 0; l--) {
		if(!bit.test(l)) continue;
		if(used[l]) bit ^= base[l], sla ^= usados[l];
		else {
			base[l] = bit;
			used[l] = 1;
			sla.set(id);
			usados[l] = sla;
			return;
		}
	}
}

bool check() {
	for(int l = n-1; l >= 0; l--) {
		if(!bit.test(l)) continue;
		if(!used[l]) return 0;
		bit ^= base[l]; sla ^= usados[l];
	}
	return 1;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			char c; scanf(" %c", &c);
			if(c == '1') bit.set(j);
		}
		insert(i);
		bit.reset();
		sla.reset();
	}

	vector<vector<int>> ans;
	bool ok = 1;
	for(int i = 0; i < n; i++) {
		bit.set(i);
		ok &= check();
		string s = sla.to_string();
		reverse(s.begin(), s.end());
		vector<int> here;
		for(int j = 0; j < n; j++)
			if(s[j] == '1') here.push_back(j+1);
		ans.push_back(here);
		bit.reset();
		sla.reset();
	}

	if(!ok) return puts("-1"), 0;
	for(int i = 0; i < n; i++) {
		for(int x : ans[i])
			printf("%d ", x);
		printf("\n");
	}
}