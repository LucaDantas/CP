#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, logn = 31;

int f[logn][maxn], a[maxn];

bool mark[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &f[0][i]), mark[f[0][i]] = 1;
	for(int i = 1; i <= n; i++)
		scanf("%d", a+i);

	int sz_add = 0, last = 0;
	for(int i = 1; i <= n; i++)
		if(!mark[i]) ++sz_add, last = i;
	
	if(a[last] <= n) {
		for(int i = 1; i <= n; i++)
			printf("%d ", a[i]);
		puts("");
		return 0;
	}

	int k = (a[last]-n)/sz_add;

	for(int l = 1; l < logn; l++)
		for(int i = 1; i <= n; i++)
			f[l][i] = f[l-1][f[l-1][i]];

	vector<vector<int>> morre(n+1, vector<int>());

	for(int i = 1; i <= n; i++) {
		int kth = i;
		for(int l = logn-1; l >= 0; l--)
			if((1<<l)&k) kth = f[l][kth];
		morre[a[kth]].push_back(i);
	}

	set<int> trash;
	vector<int> ans(n+1);

	for(int i = 1; i <= n; i++) {
		if(morre[i].size()) {
			ans[morre[i].front()] = i;
			for(int j = 1; j < (int)morre[i].size(); j++)
				trash.insert(morre[i][j]);
		} else {
			assert(trash.size());
			ans[*trash.begin()] = i;
			trash.erase(trash.begin());
		}
	}

	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	puts("");
}
