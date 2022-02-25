#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int tot = 50;

mt19937 rng(random_device{}());

int rnd(int x) { return (rng() % x + x) % x; }

void solve(int n)
{
	for(int i = 0; 2*i < tot; i++) {
		int rd = rnd(n)+1, cor = kth(rd);
		if(cnt(cor) > n/3)
			return (void)(say_answer(cor));
	}
	say_answer(-1);
}
