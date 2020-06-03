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

const int maxn = 1e6 + 100;

int a[maxn]; //1 - open, 0 - close

struct Node{
	int open, close, done;
} tree[4*maxn];

void build(int node, int l, int r) {
	if(l == r) {
		tree[node] = {a[l], a[l]^1, 0};
	}
	else {
		int mid = (l+r) >> 1;

		build(2*node, l, mid);
		build(2*node+1, mid+1, r);

		int done = min(tree[2*node].open, tree[2*node+1].close);
		tree[node].done = done + tree[2*node].done + tree[2*node+1].done;
		tree[node].open = tree[2*node].open + tree[2*node+1].open - done;
		tree[node].close = tree[2*node].close + tree[2*node+1].close - done;
	}
}

Node query(int node, int i, int j, int l, int r) {
	if(j < l || i > r)
		return {0,0,0};
	if(i >= l && j <= r)
		return tree[node];
	int mid = (i+j) >> 1;
	Node left = query(2*node, i, mid, l, r);
	Node right = query(2*node+1, mid+1, j, l, r);

	int done = min(left.open, right.close);
	Node ret;
	ret.done = left.done + right.done + done;
	ret.open = left.open + right.open - done;
	ret.close = left.close + right.close - done;
	return ret;
}

int main(){
	string s;
	cin >> s;

	int n = sz(s);
	rep(i,1,n+1) a[i] = (s[i-1] == '(');

	build(1,1,n);
	int q;
	scanf("%d", &q);
	
	while(q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		Node ans = query(1,1,n,x,y);
		printf("%d\n", 2*ans.done);
	}
}
