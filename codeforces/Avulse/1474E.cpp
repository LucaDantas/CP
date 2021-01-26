#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define pb push_back

ll sq(int x) {return 1ll*x*x;}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		ll ans = 0;
		vector<pii> op;
		vector<int> dist(n);
		for(int i = 1; i < n; i++) {
			ans += sq(max(i, n-1-i));
			if(i > n-1-i) op.pb({i, 0}), dist[i] = abs((n-1)/2 - i);
			else op.pb({i, n-1}), dist[i] = abs(n/2 - i);
		}
		sort(op.begin(), op.end(), [&](pii a, pii b){return dist[a.first] > dist[b.first];});
		
		printf("%lld\n", ans);
		vector<int> perm(n); iota(perm.begin(), perm.end(), 1);
		for(int i = 0; i < n-1; i++)
			swap(perm[op[i].first], perm[op[i].second]);
		
		for(int i = 0; i < n; i++)
			printf("%d ", perm[i]);
		printf("\n");
		
		printf("%d\n", n-1);
		for(int i = n-2; i >= 0; i--)
			printf("%d %d\n", op[i].first+1, op[i].second+1);
	}
}