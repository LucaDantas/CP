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
#define read(v, a, b) for(int i=(a); i<(b); i++) cin >> v[i];
// #define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 8e5;

struct Ins
{
	char type;
	int a, b;
};

int bit[maxn];

void update(int x, int v) {
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int main(){
	FAST; // Need to use this because scanf printf are slower and getting close tle
	int n, q; cin >> n >> q;
	// scanf("%d %d", &n, &q);
	vi a(n), pos(n+3*q);
	vector<Ins> ins(q);
	read(a,0,n);
	rep(i,0,n) pos[i] = a[i];
	int aux = n;
	rep(i,0,q) {
		// scanf(" %c %d %d", &ins[i].type, &ins[i].a, &ins[i].b);
		cin >> ins[i].type >> ins[i].a >> ins[i].b;
		if(ins[i].type == '?') pos[aux++] = ins[i].a;
		pos[aux++] = ins[i].b;
	}

	map<int, int> Mp;

	allin(it, pos)
		Mp[it];

	aux = 0;
	trav(it, Mp)
		it.ss = ++aux;

	trav(it, a)
		it = Mp[it];

	trav(it, ins) {
		if(it.type == '?') it.a = Mp[it.a];
		it.b = Mp[it.b];
	}

	allin(it, a)
		update(it, 1);

	allin(qr, ins) {
		if(qr.type == '!')
			update(a[qr.a-1], -1), update(qr.b, 1), a[qr.a-1] = qr.b;
		else
			cout << query(qr.b) - query(qr.a-1) << '\n';
			// printf("%d\n", query(qr.b) - query(qr.a-1));
	}
}
