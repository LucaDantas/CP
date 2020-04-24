#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define x first
#define y second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;

int n, k, bit[maxn+1];

pii pt[maxn];

void update(int x, int v){
	for(; x <= maxn; x+=(x&-x))
		bit[x] += v;
}

int query(int x){
	int ans=0;
	for(; x > 0; x-=(x&-x))
		ans += bit[x];
	return ans;
}

int check(int v){
	int ptr=0, ret = 0;
	for(int i = 1; i <= n; i++){ //That's the right pointer
		for(; ptr < i && pt[i].x - pt[ptr].x > v; ptr++)
			update(pt[ptr].y, 1);
		
	}
}

int bs(){
	int l = 1, r = n, ans = 0;
	while(l <= r){
		int mid = ((l+r)>>1);
		if(check(m) >= k){
			ans = m;
			r = mid -1;
		}
		else l = mid+1;
	}
	return ans;
}

int main(){
	FAST;
	cin >> n >> k;
	for(int i = 1, a, b; i <= n; i++){
		cin >> a >> b;
		pt[i] = {a, b};
	}
	sort(all(pt));
	cout << bs() << endl;
}
