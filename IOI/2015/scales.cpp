#include "scales.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)((a).size())
#define ff first
#define ss second

constexpr int maxn = 2020;

vector<vector<int>> permutacoes;
vector<pair<int, vector<int>>> operacoes;

int fim[maxn], go[maxn];

bool solve(int pos, int size, vector<int> possible) {
	if(sz(possible) <= 1) {
		if(sz(possible) == 1) {
			fim[pos] = 1;
			go[pos] = possible[0];
		}
		return true;
	}
	for(int g = 0; g < sz(operacoes); g++) {
		auto op = operacoes[g];
		bool ok = 1;
		vector<int> ans[3];
		for(int p : possible) {
			int x = permutacoes[p][op.ss[0]];
			int y = permutacoes[p][op.ss[1]];
			int z = permutacoes[p][op.ss[2]];
			int decode[6], val[3] = {x, y, z};
			sort(val, val+3);
			decode[x] = 0;
			decode[y] = 1;
			decode[z] = 2;
			if(op.ff == 1) ans[decode[val[0]]].pb(p);
			else if(op.ff == 2) ans[decode[val[1]]].pb(p);
			else if(op.ff == 3) ans[decode[val[2]]].pb(p);
			else {
				int w = permutacoes[p][op.ss[3]];
				if(w > val[2] || w < val[0]) ans[decode[val[0]]].pb(p);
				else if(w < val[1]) ans[decode[val[1]]].pb(p);
				else ans[decode[val[2]]].pb(p);
			}
		}
		if(max({sz(ans[0]), sz(ans[1]), sz(ans[2])}) > size) continue;
		for(int i : {0, 1, 2})
			ok &= solve(3*pos+i, size/3, ans[i]);
		if(ok) {
			go[pos] = g;
			return true;
		}
	}
	return false;
}

void init(int T) {
	++T;
	vector<int> vec(6);
	iota(all(vec), 0);
	do {
		permutacoes.pb(vec);
	} while(next_permutation(all(vec)));
	vector<int> list(720);
	iota(all(list), 0);
	for(int mask = 0; mask < (1<<6); mask++) {
		if(__builtin_popcount(mask) != 3) continue;
		vector<int> ligado;
		for(int i = 0; i < 6; i++)
			if(mask&(1<<i))
				ligado.pb(i);
		for(int i : {1, 2, 3})
			operacoes.pb({i, ligado});
		for(int i = 0; i < 6; i++) {
			if(mask&(1<<i)) continue;
			ligado.pb(i);
			operacoes.pb({4, ligado});
			ligado.pop_back();
		}
	}
	solve(1, 243, list);
}

int get(int pos) {
	if(fim[pos]) return go[pos];
	auto op = operacoes[go[pos]];
	int ans;
	if(op.ff == 1) ans = getLightest(op.ss[0]+1, op.ss[1]+1, op.ss[2]+1);
	else if(op.ff == 2) ans = getMedian(op.ss[0]+1, op.ss[1]+1, op.ss[2]+1);
	else if(op.ff == 3) ans = getHeaviest(op.ss[0]+1, op.ss[1]+1, op.ss[2]+1);
	else ans = getNextLightest(op.ss[0]+1, op.ss[1]+1, op.ss[2]+1, op.ss[3]+1);
	if(ans == op.ss[0]+1) return get(3*pos);
	if(ans == op.ss[1]+1) return get(3*pos+1);
	return get(3*pos+2);
}

void orderCoins() {
	int pos = get(1), W[6];
	for(int i = 0; i < 6; i++)
		W[permutacoes[pos][i]] = i+1;
	answer(W);
}