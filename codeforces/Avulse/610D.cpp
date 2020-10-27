#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using piii = pair<int,pii>;

#define pb push_back
#define ff first
#define ss second.first
#define tt second.second
#define all(a) a.begin(), a.end()
#define sz(a) (int)(a.size())

constexpr int maxn = 1e5+10;

const piii trash = {-1, {-1, -1}};

vector<piii> hor, ver;

map<int,int> mp[2];

int n, bit[maxn];

void upd(int x, int v) {
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

ll ans = 0;

bool intersect(int a, int b, int c, int d) {
	if(a > c)
		swap(a, c), swap(b, d);
	return b >= c;
}

void norm(vector<piii>& v) {
	for(int i = 1; i < sz(v); i++) {
		if(v[i].ff == v[i-1].ff && intersect(v[i].ss, v[i].tt, v[i-1].ss, v[i-1].tt))
			v[i] = {v[i].ff, {min(v[i].ss, v[i-1].ss), max(v[i].tt, v[i-1].tt)}},
			v[i-1] = trash;
	}
	vector<piii> sv;
	for(int i = 0; i < sz(v); i++)
		if(v[i] != trash)
			sv.pb(v[i]), ans += v[i].tt - v[i].ss + 1;
	v = sv;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x1, x2, y1, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if(x1 > x2)
			 swap(x1, x2);
		if(y1 > y2)
			swap(y1, y2);
		if(x1 == x2) ver.pb({x1, {y1, y2}});
		else hor.pb({y1, {x1, x2}});
		mp[0][x1], mp[0][x2], mp[1][y1], mp[1][y2];
	}
	sort(all(hor)); sort(all(ver));

	norm(hor); norm(ver);

	int cnt = 0;
	for(auto& it : mp[0])
		it.second = ++cnt;
	cnt = 0;
	for(auto& it : mp[1])
		it.second = ++cnt;

	for(piii& p : hor)
		p.ff = mp[1][p.ff], p.ss = mp[0][p.ss], p.tt = mp[0][p.tt];
	for(piii& p : ver)
		p.ff = mp[0][p.ff], p.ss = mp[1][p.ss], p.tt = mp[1][p.tt];

	sort(all(ver)); // ordeno pelo x
	sort(all(hor), [](const piii& a, const piii& b) {
		return a.ss < b.ss; // ordeno pelo começo do intervalo
	});

	int ptr = 0;
	priority_queue<pii, vector<pii>, greater<pii>> q;
	for(int i = 0; i < sz(ver); i++) {
		int x = ver[i].ff;
		for(; ptr < sz(hor) && hor[ptr].ss <= x; ptr++)
			q.push({hor[ptr].tt, hor[ptr].ff}), upd(hor[ptr].ff, 1);
		while(q.size() && q.top().ff < x)
			upd(q.top().second, -1), q.pop();
		ans -= query(ver[i].tt) - (ver[i].ss>1?query(ver[i].ss-1):0);
	}

	printf("%lld\n", ans);
}