#include "Device.h"
#include <bits/stdc++.h>
using namespace std;

constexpr double base = 1.05;

static vector<int> val;

void InitDevice() {
	val.push_back(1);
	for(int i = 1; i < (1 << 8); i++) {
		int aq = val.back() * base;
		if(aq == val.back()) ++aq;
		val.push_back(aq);
	}
}

int Answer(long long S, long long T)
{
	int in[2], out[2];
	for(int rep = 0; rep < 2; rep++, swap(S, T)) {
		in[rep] = S >> 8;
		out[rep] = in[rep] + val[S % (1<<8)] - 1;
	}
	int vira = 0;
	if(in[0] > in[1])
		swap(in[0], in[1]), swap(out[0], out[1]), vira = 1;
	return (out[0] >= in[1] ? 1^vira : 2);
}
