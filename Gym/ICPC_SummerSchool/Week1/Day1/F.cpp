#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;

struct DSU {
    int pai[maxn], peso[maxn], tam[maxn];
    void init() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1, tam[i] = 0; }
    int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
    void join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return;
        if(peso[a] < peso[b]) std::swap(a, b);
        pai[b] = a;
		peso[a] += peso[b];
		tam[a] += tam[b];
    }
} dsu;

struct BRUH {
	int x, y, w, h;
} sv[maxn];

struct LINHA {
	int pos, sz, id;
	bool operator<(LINHA b) const { return pos < b.pos; }
};

std::vector<LINHA> v[maxn];

int back[2][maxn];

std::map<int, int> mp[2];

bool touch(LINHA a, LINHA b) { if(a.pos > b.pos) std::swap(a, b); return a.pos + a.sz >= b.pos; }

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		dsu.init();
		for(int i = 0; i <= n; i++)
			back[0][i] = back[1][i] = 0, sv[i] = {0, 0, 0, 0};
		mp[0].clear(); mp[1].clear();


		for(int i = 1; i <= n; i++) {
			int x, y, w, h; scanf("%d %d %d %d", &x, &y, &w, &h);
			dsu.tam[i] = w*h;
			sv[i] = {x, y, w, h};
			
			mp[0][x] = 0;
			mp[0][x+w-1] = 0;

			mp[1][y] = 0;
			mp[1][y+h-1] = 0;
		}

		int coord[2]{};
		for(int k = 0; k < 2; k++) {
			back[k][0] = -1;
			for(auto& x : mp[k])
				back[k][1+coord[k]] = x.first, x.second = ++coord[k];
		}

		for(int k = 0; k < 2; k++) {
			if(!k) {
				for(int i = 1; i <= n; i++) {
					v[ mp[k][sv[i].x] ].push_back({sv[i].y, sv[i].h, i});
					v[ mp[k][sv[i].x+sv[i].w-1] ].push_back({sv[i].y, sv[i].h, i});
				}
			} else {		
				for(int i = 1; i <= n; i++) {
					v[ mp[k][sv[i].y] ].push_back({sv[i].x, sv[i].w, i});
					v[ mp[k][sv[i].y+sv[i].h-1] ].push_back({sv[i].x, sv[i].w, i});
				}
			}

			for(int i = 1; i <= coord[k]; i++) {
				if(back[k][i] != back[k][i-1] + 1) continue;

				std::sort(v[i].begin(), v[i].end());

				int ptr = 0;
				for(int j = 0; j < (int)v[i].size(); j++) {
					while(ptr < (int)(v[i-1].size()) && v[i][j].pos > v[i-1][ptr].pos + v[i-1][ptr].sz) ptr++;
					while(ptr < (int)(v[i-1].size()) && touch(v[i][j], v[i-1][ptr])) dsu.join(v[i][j].id, v[i-1][ptr].id), ptr++;
					ptr = max(ptr-2, 0);
				}
			}

			for(int i = 1; i <= coord[k]; i++)
				v[i].clear();
		}

		int ans = 0;
		for(int i = 1; i <= n; i++)
			ans = max(ans, dsu.tam[i]);
		printf("%d\n", ans);
	}
}
