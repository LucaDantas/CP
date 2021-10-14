#include <bits/stdc++.h>
using namespace std;

vector<unsigned int> l, r;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		l.clear(); r.clear();
		unsigned int a, b, c; cin >> a >> b >> c;
		c = (unsigned int)((1ll<<32) - c);
		for(unsigned int mask = 0; mask < (1 << 16); mask++) {
			l.push_back(a*mask*mask + b*mask);
			r.push_back(a * (mask<<16)*(mask<<16) + b*(mask<<16));
		}
		sort(l.begin(), l.end(), greater<unsigned int>());
		sort(r.begin(), r.end());
		int ptrL = 0, ptrR = 0;
		bool ok = 0;
		for(unsigned int x : l) {
			while(ptrL < (int)r.size() && r[ptrL] < c - x) ptrL++;
			if(ptrL < (int)r.size() && r[ptrL] + x == c) ok = 1;
			while(ptrR < (int)r.size() && r[ptrR] < c - x - (1ll << 32)) ptrR++;
			if(ptrR < (int)r.size() && r[ptrR] + x == c) ok = 1;
		}
		puts(ok ? "YES" : "NO");
	}
}
