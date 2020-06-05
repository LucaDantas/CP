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
	int n, d;
	scanf("%d %d", &n, &d);
	vi a(2*n+1);
	read(a,1,n+1);
	rep(i,n+1,2*n+1) a[i] = a[i-n];
	int ans = 0, sum = a[1];
	for(int l = 1, r = 1; l <= n; sum -= a[l++]) {
		if(r < l) r = l, sum = a[l];
		while(r+1 <= 2*n && sum < d) {
			sum += a[++r];
			if(r - l >= n) sum -= a[l++];
		}
		ans += (sum == d);
	}
	printf("%d\n", ans);
}
