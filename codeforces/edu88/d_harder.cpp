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

const int maxn = 1e5 + 100, inf = 0x3f3f3f3f;

int n;

int L[maxn], R[maxn], a[maxn];

void calc() {
	stack<int> s;
	
	for(int i = 1; i <= n; i++) {
		while(!s.empty() && a[i] >= a[s.top()])
			s.pop();
		L[i] = s.empty()? 1 : s.top() + 1;
		s.push(i);
	}
	
	while(!s.empty())
		s.pop();
	
	for(int i = n; i >= 1; i--) {
		while(!s.empty() && a[i] >= a[s.top()])
			s.pop();
		R[i] = s.empty()? n : s.top() - 1;
		s.push(i);
	}
}

int pref[maxn];
pii tree[4*maxn]; //min and max

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = mp(pref[i], pref[i]);
		return;
	}
	
	int mid = (i+j) >> 1;
	
	build(2*node, i, mid); build(2*node+1, mid+1, j);
	
	tree[node].ff = min(tree[2*node].ff, tree[2*node+1].ff);
	tree[node].ss = max(tree[2*node].ss, tree[2*node+1].ss);
}

//type 0 is min, type 1 = max
int query(int node, int i, int j, int l, int r, int type) {
	if(i > r || j < l)
		return (type)? -inf : inf;
		
	if(i >= l && j <= r)
		return (type)? tree[node].ss : tree[node].ff;
		
	int mid = (i+j) >> 1;
	
	if(type) 
		return max(query(2*node, i, mid, l, r, type), query(2*node+1, mid+1, j, l, r, type));
	else 
		return min(query(2*node, i, mid, l, r, type), query(2*node+1, mid+1, j, l, r, type));
	
}

int main(){
	scanf("%d", &n);
	read(a,1,n+1);
	
	rep(i,1,n+1) {
		pref[i] = pref[i-1] + a[i];
	}
	
	build(1,0,n);

	calc();
	
	int ans = 0;
	
	rep(i,1,n+1)
		if(a[i] > 0)
			ans = max(ans, query(1, 0, n, i, R[i], 1) - query(1, 0, n, L[i]-1, i-1, 0) - a[i]);
	
	printf("%d\n", ans);
}
