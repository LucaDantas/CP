#include "towns.h"
#include <bits/stdc++.h>
using namespace std;
 
constexpr int maxn = 300;
 
int dp[maxn][maxn], c[maxn];

map<int, vector<int>> filhos;
 
int get(int i, int j) {
	if(i > j) swap(i, j);
	return dp[i][j] != -1 ? dp[i][j] : dp[i][j] = getDistance(i, j);
}

int hubDistance(int N, int sub) {
	memset(dp, -1, sizeof dp);
	memset(c, 0, sizeof c);
	filhos.clear();
	int a = 0, b = 0, dist = 0;
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < N; j++) {
			if(a != j) {
				int v = get(a, j);
				if(v > dist) b = j, dist = v;
			}
		}
		if(!i) swap(a, b);
	}
	b = 0;
	int R = 0x3f3f3f3f;
	for(int i = 0; i < N; i++) {
		if(i == a || i == b) continue;
		int d1 = get(a, i), d2 = get(b, i);
		c[i] = (d1 + d2 - get(a, b)) >> 1;
		R = min(R, max(d1 - c[i], dist - d1 + c[i]));
		filhos[d1-c[i]].push_back(i);
	}

	vector<int> lista, bucket;

	int sz = 1;
	for(auto it : filhos) {
		if(it.first != R && it.first != dist - R) {
			sz += (int)(it.second).size();
			continue;
		}
		if(sz > (N >> 1) || N - sz - (int)(it.second).size() > (N >> 1)) continue;
		vector<int> v = (it.second);
		int n = (int)v.size(); sz += n;
		if(n <= (N >> 1)) return R;
		for(int i = 0; i < n; i++) {
			if(!lista.size() || get(v[i], lista.back()) == c[v[i]] + c[lista.back()]) {
				lista.push_back(v[i]);
				if(bucket.size()) lista.push_back(bucket.back()),
				bucket.pop_back();
			}
			else bucket.push_back(v[i]);
		}
		int pivo = lista.back(), cnt = (int)bucket.size();
		while(lista.size()) {
			if(cnt > (N >> 1)) break;
			if(get(pivo, lista.back()) == c[lista.back()] + c[pivo]) {
				lista.pop_back();
				if(bucket.size()) bucket.pop_back();
			}
			else {
				++cnt;
				lista.pop_back();
				if(lista.size()) lista.pop_back();
			}
		}
		if(cnt <= (N >> 1)) return R;
	}

	return -R;
}