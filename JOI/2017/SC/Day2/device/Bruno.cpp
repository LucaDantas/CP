#include "Brunolib.h"
#include <cstdio>
#include <random>

namespace sla {

constexpr int maxn = 150;

std::mt19937_64 rng_64(1012);

long long rnd() { return rng_64() & ((1ll<<60)-1); } // construo um numero aleatorio de 60 bits

bool foi = 0;
long long v[maxn];

void build() {
	foi = 1;
	for(int i = 0; i < maxn; i++)
		v[i] = rnd();
}
}

long long Bruno(int N, int A[]) {
	if(!sla::foi) sla::build();
	
	long long ans = 0;
	for(int i = 0; i < N; i++)
		if(A[i]) ans ^= sla::v[i];
	return ans;
}
