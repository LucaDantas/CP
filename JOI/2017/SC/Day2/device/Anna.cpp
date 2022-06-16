#include "Annalib.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 150;

mt19937_64 rng_64(1012);

long long rnd() { return rng_64() & ((1ll<<60)-1); } // construo um numero aleatorio de 60 bits

bool foi = 0;
long long v[maxn];

void build() {
	foi = 1;
	for(int i = 0; i < maxn; i++)
		v[i] = rnd();
}

vector<pair<long long, bitset<maxn>>> basis;

bitset<maxn> ids;

void insert(long long x, int ID) {
	ids.reset();
	if(ID != -1) ids.set(ID);

	for(auto [y, usados] : basis) {
		if((x^y) < x) {
			x ^= y;
			ids ^= usados;
		}
	}

	if(x) basis.push_back({x, ids});
}

void Anna(int N, long long X, int K, int P[]) {
	if(!foi) build();
	
	basis.clear();
	for(int i = 0, ptr = 0; i < maxn; i++) {
		if(ptr < K && P[ptr] == i) { ++ptr; continue; }
		insert(v[i], i);
	}

	insert(X, -1);
	for(int i = 0; i < N; i++)
		Set(i, ids.test(i));
}
