#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 1e6 + 10;
constexpr int mod = 1000000007;

int a[MAXN], b[MAXN];

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		rep(i,1,n+1) scanf("%d", a + i);
		rep(i,1,n+1) scanf("%d", b + i);
		rep(cnt, 0, 2) { // we do it twice for the extra to cycl
			rep(i,1,n+1) {
				if(a[i] < b[i]) {
					int j = i + 1;
					if(j > n) j = 1;
					int k = min(a[j], b[i] - a[i]);
					a[j] -= k;
					b[i] -= k;
				}
			}
		}
		bool ok = 1;
		rep(i,1,n+1) {
			if(a[i] > b[i]) ok = 0;
		}
		puts(ok? "YES":"NO");
	}
}
