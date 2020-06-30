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

vi a;

int check(int k) {
	int n = sz(a), cnt = 0;
	rep(i,0,n) {
		if(a[i] <= k) {
			cnt++;
			i++;
			if(i < n) cnt++;
		}
	}
	return cnt;
}

int check2(int k) {
	int n = sz(a), cnt = 1;
	rep(i,1,n) {
		if(a[i] <= k) {
			cnt++;
			i++;
			if(i < n) cnt++;
		}
	}
	return cnt;
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	a.resize(n);
	read(a,0,n);
	int l = 1, r = 0x3f3f3f3f, best = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(check(m) >= k)
			best = m, r = m-1;
		else
			l = m+1;
	}

	int ans2 = 0x3f3f3f3f;
	l = 1, r = 0x3f3f3f3f;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(check2(m) >= k)
			ans2 = m, r = m-1;
		else
			l = m+1;
	}
	printf("%d\n", min(best,ans2));
}
