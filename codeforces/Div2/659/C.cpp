#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb emplace_back
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 1e5 + 10;
constexpr int LOGN = 21;
constexpr int mod = 1000000007;

struct DSU
{
	int pai[25];

	DSU() {
		rep(i,0,25) pai[i] = i;
	}

	int find(int x) {
		if(pai[x] == x) return x;
		return pai[x] = find(pai[x]);
	}
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if(a == b) return false;
		pai[b] = a;
		return true;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) {
		DSU dsu;
		int n, ans = 0; cin >> n;
		string a, b; cin >> a >> b;

		bool ok = 1;
		rep(i,0,n)
			if(a[i] > b[i]) {
			ok = 0;
			break;
		}
		if(!ok) { cout << "-1" << '\n'; continue; }

		rep(i,0,n) {
			if(a[i] == b[i]) continue;
			int u = a[i] - 'a', v = b[i] - 'a';
			if(dsu.join(u, v)) ans++;
		}

		cout << ans << '\n';
	}
}
