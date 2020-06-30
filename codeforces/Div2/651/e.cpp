#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 1e6+10;

set<int> z, o;

char s[maxn], t[maxn];

void solve(int i) {
	if(s[i]-'0') {
		// In this case we have a 1 misplaced and we need to find the first one in t misplaced
		if(z.empty()) {
			puts("-1");
			exit(0);
		}
		auto it = z.upper_bound(i); // first 1 misplaced in the second string
		if(it == z.end()) return;
		o.erase(i); // consume this guy now
		int aux = *it;
		z.erase(it); // consume that guy's pair
		auto nxt = o.upper_bound(aux);
		if(nxt == o.end()) return;
		auto nxt_pair = z.upper_bound(*nxt);
		if(nxt_pair == z.end()) return;
		solve(*nxt);
	}

	else {
		// In this case we have a 1 misplaced and we need to find the first one in t misplaced
		if(o.empty()) {
			puts("-1");
			exit(0);
		}
		auto it = o.upper_bound(i); // first 1 misplaced in the second string
		if(it == o.end()) return;
		z.erase(i); // consume this guy now
		int aux = *it;
		o.erase(it); // consume that guy's pair
		auto nxt = z.upper_bound(aux);
		if(nxt == z.end()) return;
		auto nxt_pair = o.upper_bound(*nxt);
		if(nxt_pair == o.end()) return;
		solve(*nxt);
	}
}

int main(){
	int n; scanf("%d", &n);

	scanf(" %s", s);
	scanf(" %s", t);
	
	rep(i,0,n) {
		if(s[i] == t[i]) continue;
		if(s[i]-'0') o.insert(i);
		else z.insert(i);
	}

	int ans = 0;
	rep(i,0,n) {
		if(z.count(i) || o.count(i)) {
			solve(i);
			ans++;
		}
	}

	// printf("%s\n", s);
	// printf("%s\n", t);

	printf("%d\n", ans);
}
