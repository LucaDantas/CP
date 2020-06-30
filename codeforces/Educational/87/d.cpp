#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e6 + 100;

int bit[maxn+10];

void upd(int x, int v){
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x){
	int ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int main(){
	int n, q; scanf("%d %d", &n, &q);
	
	for(int i = 0; i < n; i++){
		int v; scanf("%d", &v);
		upd(v, 1);
	}
	
	rep(i,0,q){
		int v; scanf("%d", &v);
		if(v > 0) upd(v, 1);
		else{
			v *= -1;
			int l = 0, r = maxn, ans;
			while(l <= r){
				int mid = ((l+r)>>1);
				if(query(mid) >= v)
					ans = mid, r = mid-1;
				else
					l = mid+1;
			}
			upd(ans, -1);
		}
	}
	int l = 0, r = maxn, ans = 0;
	while(l <= r){
		int mid = ((l+r)>>1);
		if(query(mid) > 0)
			ans = mid, r = mid-1;
		else
			l = mid+1;
	}
	printf("%d\n", ans);
}
