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

const int maxn = 1e5 + 100;

bool equal(multiset<int> a, multiset<int> b) {
	auto it2 = b.begin();
	for(auto it = a.begin(); it != a.end();) {
		// db(*it); db(*it2);
		if(*it != *it2) return false;
		++it;
		++it2;
	}
	return true;
}

int main(){
	int T; scanf("%d", &T);
	while(T--) {
		int n; scanf("%d", &n);
		vi a(n); multiset<int> s, final;
		read(a,0,n);
		allin(it, a) s.insert(it);
		// db(sz(s));
		// allin(item, s) db(item);
		bool gut = false;
		for(int k = 1; k <= 1024; k++) {
			allin(it, a) final.insert(it^k);
			// db(sz(s));
			if(equal(s, final)) {printf("%d\n", k); gut = true; break;}
			final.clear();
		}
		if(!gut) printf("-1\n");
	}
}
