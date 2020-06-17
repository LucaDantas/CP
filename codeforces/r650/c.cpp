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

int main(){
	int n; scanf("%d", &n);
	vector<bool> top(n+1);
	vi a(n);
	set<int> s;
	read(a,0,n);
	rep(i,0,n) top[a[i]] = 1;
	rep(i,0,n+1) if(!top[i]) s.insert(i);
	// In the set we have all the values that can be used in this moment, that is
	// Are not needed for any next value, and we're going to select always the smallest of those
	vi ans;
	rep(i,0,n) {
		int menor = *s.begin();
		s.erase(menor);
		ans.pb(menor);
		if(i != n-1 && a[i] != a[i+1])
			s.insert(a[i]);
	}
	rep(i,0,n) printf("%d%c", ans[i], " \n"[i==n-1]);
}
