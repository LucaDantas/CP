// Subtask with M convex hulls + ternary search + pq
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include<cassert>
#include<queue>

constexpr int maxn = 2e3+10;

struct Pt
{
	int x, y, id;
	Pt(int _x, int _y, int _id = 0) : x(_x), y(_y), id(_id) {}
	Pt() {}
	Pt operator-(Pt a) { return Pt(x-a.x, y-a.y); }
	long long operator/(Pt a) { return 1ll*x*a.y - 1ll*y*a.x; }
	long long operator*(Pt a) { return 1ll*x*a.x + 1ll*y*a.y; }
	bool operator<(Pt a) { return x == a.x ? y < a.y : x < a.x; }
	void db() { printf("db %d %d\n", x, y); }
} pts[maxn];

bool ccw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) > 0; }
bool cw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) < 0; }

std::vector<Pt> hull[20];

std::priority_queue<std::array<long long,3>> q;

std::vector<std::pair<int,int>> limpar;

bool vis[20][maxn], mark[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int x, y, k; scanf("%d %d %d", &x, &y, &k);
		pts[i] = Pt(x, y, i);
		for(int j = 0, trash; j < k; j++)
			scanf("%d", &trash);
	}
	std::sort(pts, pts+n);
	for(int k = 0; k < m; k++) {
		int mx = 0;
		for(int i = 0; i < n; i++) {
			if(mark[pts[i].id]) continue;
			while(hull[k].size() >= 2 && !cw(hull[k][(int)hull[k].size()-2], hull[k].back(), pts[i]))
				hull[k].pop_back();
			hull[k].push_back(pts[i]); mx = std::max(mx, pts[i].y);
		}
		reverse(hull[k].begin(), hull[k].end());
		while(hull[k].size() && hull[k].back().y < mx) hull[k].pop_back();
		reverse(hull[k].begin(), hull[k].end());
		for(Pt p : hull[k])
			mark[p.id] = 1;
	}
	int Q; scanf("%d", &Q);
	while(Q--) {
		int A, B; scanf("%d %d", &A, &B);
		Pt p(A, B);
		auto search = [&](int k) {
			int l = 0, r = (int)(hull[k].size())-1;
			while(l < r) {
				int mid = (l+r) >> 1;
				if(p*hull[k][mid] > p*hull[k][mid+1]) r = mid;
				else l = mid+1;
			}
			return l;
		};
		while(q.size()) q.pop();
		long long ans = 0;
		limpar.clear();
		int i = 0;
		for(int ind = 0; i < m; ind++) {
			if(!hull[ind].size()) break;
			int pos_atual = search(ind);
			while(q.size() && i < m) {
				auto [val, pos, k] = q.top();

				if(val < p*hull[ind][pos_atual]) break;

				limpar.push_back({k, pos});
				q.pop();

				ans += val; ++i;
				vis[k][pos] = 1;
				if(pos+1 < (int)hull[k].size() && !vis[k][pos+1])
					q.push({(p*hull[k][pos+1]), pos+1, k});
				if(pos && !vis[k][pos-1])
					q.push({(p*hull[k][pos-1]), pos-1, k});
			}
			q.push({p*hull[ind][pos_atual], pos_atual, ind});
		}
		while(q.size() && i < m) {
			auto [val, pos, k] = q.top();
			limpar.push_back({k, pos});

			q.pop();
			ans += val; ++i;
			vis[k][pos] = 1;
			if(pos+1 < (int)hull[k].size() && !vis[k][pos+1])
				q.push({(p*hull[k][pos+1]), pos+1, k});
			if(pos && !vis[k][pos-1])
				q.push({(p*hull[k][pos-1]), pos-1, k});
		}
		for(auto par : limpar)
			vis[par.first][par.second] = 0;
		printf("%lld\n", ans);
	}
}