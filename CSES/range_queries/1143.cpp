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

// What we want to do is to find the first value that is greater or equal to v
// To do this we'll do a max-seg and the function find we'll choose where to go
// depending on the max of the left segment, if the max-value of the left segment
// if it is greater or equal to v we go to the left and if the value is smaller than v
// we'll go to the right side, and if there is no value in the whole interval that fits
// that value we need we return 0

// I'll do this 0-check at the end - did it by checking tree[1], which has teh greatest value

const int maxn = 2e5 + 100, inf = 0x3f3f3f3f;

int a[maxn], tree[4*maxn];

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = a[i];
	}
	else {
		int mid = (i+j) >> 1;
		build(2*node, i, mid);
		build(2*node+1, mid+1, j);

		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		tree[node] -= val;
	}
	else {
		int mid = (i+j) >> 1;
		if(pos <= mid) update(2*node, i, mid, pos, val);
		else update(2*node+1, mid+1, j, pos, val);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
}

int find(int node, int i, int j, int v) {
	if(i == j) return i;

	int mid = (i+j) >> 1;

	if(tree[2*node] >= v) return find(2*node, i, mid, v);
	else return find(2*node+1, mid+1, j, v);
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	read(a,1,n+1);
	build(1,1,n);
	while(m--) {
		int v;
		scanf("%d", &v);
		if(tree[1] >= v){
			int pos = find(1,1,n,v);
			update(1,1,n,pos,v);
			printf("%d\n", pos);
		}
		else {
			printf("0\n");
		}
	}
}
