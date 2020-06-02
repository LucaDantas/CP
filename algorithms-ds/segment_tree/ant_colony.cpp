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

const int maxn = 1e5 + 100, inf = 0x7fffffff;

int arr[maxn];

int gcd(int x, int y) {
	if(!y) return x;
	return gcd(y, x%y);
}

struct Node {
	pii mn;
	int gcd;
} tree[4*maxn];

void build(int node, int l, int r) {
	if(l == r) {
		tree[node] = {mp(arr[l], 1), arr[l]};
	} else {
		int mid = (l+r) >> 1;
		
		build(2*node, l, mid);
		build(2*node+1, mid+1, r);
		
		if(tree[2*node].mn.ff == tree[2*node+1].mn.ff)
			tree[node].mn = mp(tree[2*node].mn.ff, tree[2*node].mn.ss + tree[2*node+1].mn.ss);
		else
			tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
		tree[node].gcd = gcd(tree[2*node].gcd, tree[2*node+1].gcd);
	}
}

Node query(int node, int l, int r, int a, int b) {
	if(l > b || r < a)
		return {mp(inf, 0), 0};
	if(l >= a && r <= b)
		return tree[node];
	int mid = (l+r) >> 1;
	
	Node ret;
	Node left = query(2*node, l, mid, a, b);
	Node right = query(2*node+1, mid+1, r, a, b);
	
	if(left.mn.ff == right.mn.ff)
		ret.mn = mp(left.mn.ff, left.mn.ss + right.mn.ss);
	else
		ret.mn = min(left.mn, right.mn);
	ret.gcd = gcd(left.gcd, right.gcd);
	return ret;
}

int main(){
	int n;
	scanf("%d", &n);
	read(arr,1,n+1);
	int q; scanf("%d", &q);
	build(1,1,n);
	while(q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		int ans = r - l + 1; //total number of ants
		Node qry = query(1,1,n,l,r);
		pii mn = qry.mn;
		int gcd = qry.gcd;
		if(gcd % mn.ff == 0) ans -= mn.second;
		printf("%d\n", ans);
	}
}
