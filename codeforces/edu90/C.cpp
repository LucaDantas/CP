#include <bits/stdc++.h>
using namespace std;

#define int long long

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

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
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int32_t main() {
	int t; cin >> t;
	while(t--) {
		string s; cin >> s;
		int n = sz(s);
		vi pos(n, -1);
		int atual = 0, ans = 0;
		rep(i,0,n) {
			if(s[i] == '+') atual++;
			else atual--;
			if(atual < 0) {
				if(pos[-atual - 1] == -1) pos[-atual - 1] = i;
			}
		}
		rep(i,0,n) {
			if(pos[i] != -1) ans += pos[i]+1;
		}
		cout << ans + n << '\n';
	}
}
