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

const int maxn = (1<<18);

int a[maxn], tree[2*maxn];

void build(int node, int l, int r, int level) {
	if(l == r){
		tree[node] = a[l];
	}
	else {
		int mid = (l+r) >> 1;
		build(2*node, l, mid, level-1);
		build(2*node+1, mid+1, r, level-1);

		if(level&1) {
			//odd level is bitwise or (aka |)
			tree[node] = tree[2*node]|tree[2*node+1];
		}
		else {
			//even level is bitwise exclusive or (aka ^)
			tree[node] = tree[2*node]^tree[2*node+1];
		}
	}
}

void update(int node, int l, int r, int level, int pos, int val) {
	if(l == r) {
		tree[node] = val;
		a[pos] = val;
	}
	else {
		int mid = (l+r) >> 1;
		if(pos <= mid) {
			update(2*node, l, mid, level-1, pos, val);
		}
		else {
			update(2*node+1, mid+1, r, level-1, pos, val);
		}
		if(level&1) {
			tree[node] = tree[2*node]|tree[2*node+1];
		}
		else {
			tree[node] = tree[2*node]^tree[2*node+1];
		}
	}
}

int main(){
	int n, m, pown;
	scanf("%d %d", &n, &m);
	pown = 1<<n;
	rep(i,1,pown+1)
		scanf("%d", &a[i]);
	build(1,1,pown, n);
	while(m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		update(1, 1, pown, n, x, y);
		printf("%d\n", tree[1]);
	}
}
