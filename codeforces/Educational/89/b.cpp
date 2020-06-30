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

int main(){
	int t; scanf("%d", &t);
	while(t--) {
		int n, x, m, l, r; scanf("%d %d %d", &n, &x, &m);
		l = r = x;
		while(m--) {
			int a, b; scanf("%d %d", &a, &b);
			if((a <= r && a >= l) || (b <= r && b >= l) || (a <= l && b >= r)) l = min(l,a), r = max(r,b);
		}
		printf("%d\n", r-l+1);
	}
}
