#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e6+10, logn = 22;

int a[maxn];

struct Query { int x, e; } qr[maxn];

set<pair<int,int>, greater<pair<int,int>>> st;

int main() {
	int n, start; scanf("%d %d", &n, &start);
	for(int i = 1; i <= n; i++)
		scanf("%d", a+i), st.insert({a[i], i});
	
	int q; scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		char c; scanf(" %c", &c);
		if(c == 'E') {
			scanf("%d %d", &qr[i].x, &qr[i].e);
		} else {
			int x; scanf("%d", &x);
			qr[i] = {x, -1};
		}
	}
	
	vector<int> l, r; // salvo os dois paretos

	for(int i = start+1; i <= n; i++)
		if(!r.size() || a[i] > a[r.back()])
			r.push_back(i);
	r.push_back(n+1); a[n+1] = 0x3f3f3f3f;

	for(int i = start-1; i >= 1; i--)
		if(!l.size() || a[i] > a[l.back()])
			l.push_back(i);
	l.push_back(0); a[0] = 0x3f3f3f3f;

	for(int i = 1; i <= q; i++) {
		if(qr[i].e == -1) {
			// query
			int x = qr[i].x;

			if(x == start) puts("0");
			else if(x > start) {
				auto mx = *(--upper_bound(r.begin(), r.end(), x));

				int L = 0, R = (int)(l.size())-1, ans = 1;
				while(L <= R) {
					int M = (L+R) >> 1;
					if(a[l[M]] > a[mx])
						ans = l[M]+1, R = M-1;
					else
						L = M+1;
				}

				printf("%d\n", x - ans); // não inclui x

			} else {
				auto mx = *lower_bound(l.rbegin(), l.rend(), x);

				int L = 0, R = (int)(r.size())-1, ans = n;
				while(L <= R) {
					int M = (L+R) >> 1;
					if(a[r[M]] > a[mx])
						ans = r[M]-1, R = M-1;
					else
						L = M+1;
				}

				printf("%d\n", ans - x); // não inclui x
			}
		} else {
			auto [x, pos] = qr[i];
			int val = st.begin()->first+1;
			
			vector<pair<int,int>> add;
			for(int k = 1; k < pos; k++) {
				int id = st.begin()->second;
				st.erase(st.begin());
				val = a[id];
				++a[id];
				add.push_back({a[id], id});
			}
			
			for(auto p : add)
				st.insert(p);
 
			assert(st.find({a[x], x}) != st.end());
			st.erase({a[x], x});
			a[x] = val;
			st.insert({a[x], x});

			if(x < start) swap(l, r);

			vector<int> sv;
			while(r.size() && (x > start ? r.back() > x : r.back() < x))
				sv.push_back(r.back()), r.pop_back();

			sv.push_back(x);
			reverse(sv.begin(), sv.end());

			for(int x : sv)
				if(!r.size() || a[x] > a[r.back()])
					r.push_back(x);

			if(x < start) swap(l, r);
		}
	}
}
