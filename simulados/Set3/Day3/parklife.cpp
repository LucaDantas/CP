#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

constexpr int maxn = 3e5+10, maxv = 1e6+10;

struct Seg
{
	int l, r, v, idx;
	bool operator<(const Seg& o) const { return r - l < o.r - o.l; }
} segments[maxn];

bool mark[maxv];
int pai[maxv], ativo[maxv];

int nxt(int u) { return !mark[u] ? u : pai[u] = nxt(pai[u]); }

std::priority_queue<long long> val[maxv];

void merge(std::priority_queue<long long>& a, std::priority_queue<long long>& b) {
	if(a.size() < b.size()) std::swap(a, b);
	std::vector<long long> add;
	while(b.size())
		add.push_back(a.top() + b.top()), a.pop(), b.pop();
	for(long long x : add)
		a.push(x);
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < maxv; i++)
		pai[i] = i+1;
	
	for(int i = 0; i < maxv; i++)
		mark[i] = 1;
	
	for(int i = 0; i < n; i++)
		scanf("%d %d %d", &segments[i].l, &segments[i].r, &segments[i].v),
		mark[segments[i].l] = mark[segments[i].r] = 0, segments[i].idx = i+1;
	
	mark[maxv-1] = 0;

	std::sort(segments, segments+n);

	for(int s = 0; s < n; s++) {
		auto [l, r, v, idx] = segments[s];
		int pos = l;
		while(pos < r) {
			mark[pos] = 1;
			if(ativo[pos]) merge(val[idx], val[ativo[pos]]);
			ativo[pos] = 0;
			pos = nxt(pos);
		}
		mark[l] = 0;
		val[idx].push(v);
		ativo[l] = idx;
	}

	std::priority_queue<long long> ans;
	for(int i = 0; i < maxv; i++)
		if(ativo[i]) merge(ans, val[ativo[i]]);

	int a = 0;
	long long opa = 0;
	for(; ans.size(); a++)
		opa += ans.top(), ans.pop(), printf("%lld ", opa);
	for(; a < n; a++)
		printf("%lld ", opa);
	puts("");
}