#include<bits/stdc++.h>
#include "cave.h"
using namespace std;

#define pb push_back

constexpr int maxn = 5010;

int correspond[maxn], a[maxn], state[maxn];

vector<int> livre;

void exploreCave(int n) {
	for(int i = 0; i < n; i++)
		livre.pb(i);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			a[j] = state[j];
		int now = tryCombination(a);
		now = now>i||now==-1;
		int l = 0, r = n-1-i;
		while(l < r) {
			int m = (l+r) >> 1;
			for(int j = l; j <= m; j++)
				a[livre[j]] ^= 1;
			int opa = tryCombination(a);
			opa = opa>i||opa==-1;
			if(opa != now)
				r = m, now = opa;
			else l = m+1;
		}
		correspond[livre[l]] = i;
		state[livre[l]] = 1^now^a[livre[l]];
		livre.erase(livre.begin()+l);
	}
	answer(state, correspond);
}
