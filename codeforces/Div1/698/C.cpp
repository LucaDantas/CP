#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e3+10;

pair<int,int> pt[maxn];

bool mark[maxn];

inline long long sq(int a) {return 1ll*a*a;}

inline long long dist(int a, int b) {
	return sq(pt[a].first - pt[b].first) + sq(pt[a].second - pt[b].second);
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0, a, b; i < n; i++)
		scanf("%d %d", &a, &b), pt[i] = {a, b};
	int now = 0;
	for(int i = 0; i < n; i++) {
		mark[now] = 1;
		printf("%d ", now+1);
		pair<long long,int> prox;
		for(int j = 0; j < n; j++)
			if(!mark[j])
				prox = max(prox, {dist(now, j), j});
		now = prox.second;
	}
	printf("\n");
}