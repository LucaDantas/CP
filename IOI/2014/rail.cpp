#include "rail.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)((a).size())

constexpr int maxn = 5010;

bool mark[maxn], lado[maxn];

int dp[maxn][maxn];

int dist(int a, int b) { return dp[a][b] ? dp[a][b] : dp[a][b] = getDistance(a, b); }

void findLocation(int N, int first, int location[], int stype[])
{
	int menor = 0, d = 0x3f3f3f3f;
	for(int i = 1; i < N; i++)
		if(dist(0, i) < d) menor = i, d = dist(0, i);
	location[0] = first; stype[0] = 1;
	location[menor] = first + d; stype[menor] = 2;
	vector<int> l, r;

	for(int i = 1; i < N; i++) {
		if(i == menor) continue;
		if(dist(0, i) == d + dist(menor, i)) l.pb(i);
		else r.pb(i), lado[i] = 1;
	}
	
	sort(all(l), [](int x, int y) { return dp[0][x] < dp[0][y]; });
	sort(all(r), [](int x, int y) { return dp[0][x] < dp[0][y]; });
	
	for(int i = 0; i < sz(r);) {
		location[r[i]] = location[0] + dist(0, r[i]); stype[r[i]] = 2;
		int j = i+1;
		for(; j < sz(r); j++) {
			int certo = i;
			for(int k = 0; k < i; k++)
				if(stype[r[k]] == 2 && dist(r[k], r[j]) < dist(r[i], r[j]))
					{certo = k; break;}
			bool condicao = dist(0, r[j]) == dist(0, r[certo]) + dist(r[certo], r[j]);
			if(condicao)
				location[r[j]] = location[r[certo]] - dist(r[certo], r[j]), stype[r[j]] = 1;
			else break;
		}
		i = j;
	}
	
	for(int i = 0; i < sz(l);) {
		location[l[i]] = location[menor] - dist(menor, l[i]); stype[l[i]] = 1;
		int j = i+1;
		for(; j < sz(l); j++) {
			int certo = i;
			for(int k = 0; k < i; k++)
				if(stype[l[k]] == 1 && dist(l[k], l[j]) < dist(l[i], l[j]))
					{certo = k; break;}
			bool condicao = dist(0, l[j]) == dist(0, l[certo]) + dist(l[certo], l[j]);
			if(condicao)
				location[l[j]] = location[l[certo]] + dist(l[certo], l[j]), stype[l[j]] = 2;
			else break;
		}
		i = j;
	}
}
