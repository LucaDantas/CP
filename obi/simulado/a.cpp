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
	int n;
	vi a(4);
	scanf("%d", &n);
	rep(i,1,4) {
		scanf("%d", &a[i]);
	}
	sort(all(a));
	vi pref(4);
	rep(i,1,4) {
		pref[i] = pref[i-1] + a[i];
	}
	int ans = 0;
	rep(i,1,4) {
		if(n >= pref[i]) ans = i;
	}
	printf("%d\n", ans);
}
