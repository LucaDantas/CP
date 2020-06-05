#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
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

const int maxn = 2e5 + 100;
int bit[maxn+1], a[maxn], n;

void update(int x, int v){
	for(; x <= n; x+=(x&-x))
		bit[x] += v;
}
		
int query(int x){
	int ans = 0;
	for(; x > 0; x-=(x&-x))
		ans+=bit[x];
	return ans;
}

int bs(int pos){
	int l = 1, r = n, ans = n;
	while(l <= r){
		int m = ((l+r)>>1);
		if(query(m) >= pos){
			ans = m;
			r = m-1;
		}
		else l = m+1;
	}
	return ans;
}

int main(){
	FAST;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		update(i,1);
	}
	rep(i, 0, n){
		int kkk;
		cin >> kkk;
		int pos = bs(kkk);
		cout << a[pos] << endl;
		update(pos, -1);
	}
}
