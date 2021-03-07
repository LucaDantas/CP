#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 3e5+10, shift = 1000000011;

struct Circle
{
	int x, y, r, id;
} cc[maxn];

long long sq(int x) { return 1ll * x * x; }
bool intersect(Circle a, Circle b) {
	return sq(a.x - b.x) + sq(a.y - b.y) <= sq(a.r + b.r);
}

int B, n, ans[maxn];

vector<vector<Circle>> blocks;

void setBlocks() {
	sort(cc, cc+n, [](Circle a, Circle b) {
		if((a.x>>B) != (b.x>>B)) return a.x < b.x;
		return a.y < b.y;
	});
	vector<Circle> here = {cc[0]};
	for(int i = 1, last = cc[0].x; i < n; i++) {
		if((last>>B) == (cc[i].x>>B)) here.pb(cc[i]);
		else blocks.pb(here), here = {cc[i]};
		last = cc[i].x;
	}
	blocks.pb(here);
}

void doit(int i, int c) {
	int L = 0, R = (int)blocks[i].size()-1, best = -1, index = (cc[c].y>>B);
	while(L <= R) {
		int m = (L+R) >> 1;
		if((blocks[i][m].y>>B) >= index-2) best = m, R = m-1;
		else L = m+1;
	}
	if(best == -1) return;
	for(; best < (int)blocks[i].size() && (blocks[i][best].y>>B) <= index+2; ++best) {
		if(intersect(cc[c], blocks[i][best]) && !ans[blocks[i][best].id])
			ans[blocks[i][best].id] = cc[c].id+1;
	}
}

void rescale() {
	vector<vector<Circle>> aux;
	for(vector<Circle> BLOCO : blocks) {
		int index1 = ~(1<<31);
		for(Circle c : BLOCO)
			if(!ans[c.id])
				index1 = min(index1, (c.x>>B));
		if(index1 == (~(1<<31))) continue;
		vector<Circle> grp[2];
		for(Circle c : BLOCO)
			if(!ans[c.id])
				grp[(c.x>>B) != index1].pb(c);
		for(int b : {0, 1})
			if(grp[b].size()) aux.pb(grp[b]);
	}
	blocks = aux;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d %d %d", &cc[i].x, &cc[i].y, &cc[i].r);
		cc[i].x += shift; cc[i].y += shift;
		cc[i].id = i; B = max(B, cc[i].r);
	}
	B = 32 - __builtin_clz(B-1);
	setBlocks();

	sort(cc, cc+n, [](Circle a, Circle b) {
		if(a.r == b.r) return a.id < b.id;
		return a.r > b.r;
	});
	for(int i = 0; i < n; i++) {
		if(ans[cc[i].id]) continue;
		auto [x, y, r, id] = cc[i];
		while((1 << B) >= (r << 1))
			--B, rescale();

		int L = 0, R = (int)blocks.size()-1, best = -1, index = (x>>B);
		while(L <= R) {
			int m = (L+R) >> 1;
			if((blocks[m][0].x>>B) >= index-2) best = m, R = m-1;
			else L = m+1;
		}

		while(best < (int)blocks.size() && (blocks[best][0].x>>B) <= index+2)
			doit(best, i), ++best;
	}

	for(int i = 0; i < n; i++)
		printf("%d ", ans[i]);
	puts("");
}