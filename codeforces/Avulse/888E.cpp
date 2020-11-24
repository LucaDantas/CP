#include<bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())
#define pb push_back

void brute(vector<int> a, set<int>& s, int m) {
	for(int x : a) {
		vector<int> add;
		for(int it : s)
			add.pb((it+x) % m);
		for(int it : add)
			s.insert(it);
		s.insert(x);
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	vector<int> a((n+1)/2), b(n/2);
	for(int& x : a)
		scanf("%d", &x), x %= m;
	for(int& x : b)
		scanf("%d", &x), x %= m;
	set<int> s1, s2;
	brute(a, s1, m);
	brute(b, s2, m);

	s1.insert(0), s2.insert(0);

	int ans = 0;
	for(int x : s1) {
		int prox;
		auto it = s2.lower_bound(m - x);
		if(it == s2.begin())
			prox = 0;
		else prox = *(--it);
		ans = max(ans, x + prox);

		it = s2.lower_bound(2*m - x);
		if(it == s2.begin())
			prox = 0;
		else prox = *(--it);
		ans = max(ans, x + prox - m);
	}
	printf("%d\n", ans);
}