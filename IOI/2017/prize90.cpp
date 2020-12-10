#include<bits/stdc++.h>
using namespace std;
#include "prize.h"
 
constexpr int maxn = 2e5;
 
const vector<int> good = {0, 0};
 
struct BIT
{
	int bit[maxn];
 
	void build() {
		for(int i = 1; i < maxn; i++)
			bit[i] = i&-i;
	}
 
	void upd(int x, int v) {
		for(x++; x < maxn; x += x&-x)
			bit[x] += v;
	}
 
	int query(int x) {
		int ans = 0;
		for(x++; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
 
	int bs(int x) {
		int pos = 0;
		for(int l = 20; l >= 0; l--) {
			if(pos + (1 << l) >= maxn) continue;
			if(bit[pos + (1 << l)] < x)
				pos += (1 << l), x -= bit[pos];
		}
		return pos;
	}
} bit1, bit2;
 
int find_best(int n) {
	bit1.build();
	int base = 0;
	for(int i = 0; i < min(n, 475); i++) {
		vector<int> a = ask(i);
		base = max(base, a[0]+a[1]);
	}
 
	int qtd = 1;
	while(1) {
		int l = 0, r = n-qtd;
		while(1) {
			int m = (l+r) >> 1;
			int pos = bit1.bs(m);
			++qtd;
			bit1.upd(pos, -1);
			vector<int> a = ask(pos);
			if(a == good) return pos;
			if(a[0]+a[1] == base) {
				if(a[0]-bit2.query(pos)) r = m-1;
				else l = m+1;
			} else {
				bit2.upd(pos, 1);
				break;
			}
		}
	}
}